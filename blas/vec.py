#!/usr/bin/env python3

import numpy as np
import pathlib
import ctypes
import time
import sys

def load_clib(libname):
  libpath = pathlib.Path().absolute() / libname
  clib = ctypes.CDLL(libpath)
  return clib


C = load_clib("_mmul.so")
C2 = load_clib("_mmul2.so")

def _pre(a, b):

  a_ptr = a.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
  b_ptr = b.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

  M = a.shape[0]; N = b.shape[1]; K = b.shape[0]
  TA, TB = 0, 0

  c = np.zeros((M, N), dtype='float32')
  c_ptr = c.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

  assert(M == N == K)
  assert(M == 8 or M == 16 or M == 32)
  assert(TA == TB == 0)
  C2._mmul2_32_32_32_NN(c_ptr, a_ptr, b_ptr)

  return c

def _dot(a, b):

  a_ptr = a.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
  b_ptr = b.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

  M = a.shape[0]; N = b.shape[1]; K = b.shape[0]
  TA, TB = 0, 0

  c = np.zeros((M, N), dtype='float32')
  c_ptr = c.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

  C._mmul0(M, N, K, c_ptr, a_ptr, b_ptr, TA, TB)

  return c
  #return np.dot(a, b)

#def testC(M, N, K, TA, TB):
#
#  a = np.fromfile("a.bin", dtype=np.float32).reshape(M, K)
#  b = np.fromfile("b.bin", dtype=np.float32).reshape(K, N)
#  #c = np.fromfile("c.bin", dtype=np.float32).reshape(M, N)
#  c = np.zeros((M, N), dtype='float32')
#
#  a_ptr = a.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
#  b_ptr = b.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
#  c_ptr = c.ctypes.data_as(ctypes.POINTER(ctypes.c_float))
#
#  t0 = time.time()
#  C._mmul0(M, N, K, c_ptr, a_ptr, b_ptr, TA, TB)
#  t_delta = time.time() - t0
#
#  print(f'{t_delta :.6f} s')
#  print(c)
#
def test0(M, N, K, TA, TB):

  a = np.fromfile("a.bin", dtype=np.float32).reshape(M, K)
  b = np.fromfile("b.bin", dtype=np.float32).reshape(K, N)
  c = np.fromfile("c.bin", dtype=np.float32).reshape(M, N)

  t0 = time.time()
  if TA == 0 and TB == 0: c0 = _dot(a  , b  )
  if TA == 0 and TB == 1: c0 = _dot(a  , b.T)
  if TA == 1 and TB == 0: c0 = _dot(a.T, b  )
  if TA == 1 and TB == 1: c0 = _dot(a.T, b.T)
  t_delta = time.time() - t0

  print(f'{t_delta :.6f} s')

  print('c0')
  print(c0)
  print('norm c')
  print(np.linalg.norm(c))
  print('max diff')
  print(np.max(c - c0))

def test1(M, N, K, TA, TB):

  a = np.random.randn(M, K).astype('float32')
  b = np.random.randn(K, N).astype('float32')

  if TA == 0 and TB == 0:

    t0 = time.time()
    c0 = np.dot(a  , b  )
    t_delta_n = time.time() - t0

    t0 = time.time()
    c1 =   _dot(a  , b  )
    t_delta_c = time.time() - t0

    t0 = time.time()
    c2 =   _pre(a  , b  )
    t_delta_c2 = time.time() - t0

  if TA == 0 and TB == 1:
    c0 = np.dot(a  , b.T)
    c1 =   _dot(a  , b.T)

  if TA == 1 and TB == 0:
    c0 = np.dot(a.T, b  )
    c1 =   _dot(a.T, b  )

  if TA == 1 and TB == 1:
    c0 = np.dot(a.T, b.T)
    c1 =   _dot(a.T, b.T)

  print(f'pre t {t_delta_c2 :.6f} s')
  print(f'c t {t_delta_c :.6f} s')
  print(f'np t {t_delta_n :.6f} s')
  GF = (M * N * K * 2) / (t_delta_c * 1e9)
  print(f'{GF:.2f}')

  print(np.max(c1 - c0))
  print(np.max(c2 - c0))

if __name__ == "__main__":

  np.set_printoptions(precision=3)

  if len(sys.argv) > 1:
    M = int(sys.argv[1], 10)
    N = int(sys.argv[2], 10)
    K = int(sys.argv[3], 10)
    TA = int(sys.argv[4], 10)
    TB = int(sys.argv[5], 10)
    print('ta', TA, 'tb', TB)
    test1(M, N, K, TA, TB)
  else:
    print(f'usage: {sys.argv[0]} M N K tA tB')

