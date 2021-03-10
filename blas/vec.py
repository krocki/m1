#!/usr/bin/env python3

import numpy as np
import time
import sys

def test(N):

  a = np.fromfile("a.bin", dtype=np.float32).reshape(N, N)
  b = np.fromfile("b.bin", dtype=np.float32).reshape(N, N)
  c = np.fromfile("c.bin", dtype=np.float32).reshape(N, N)

  np.set_printoptions(precision=3)

  t0 = time.time()
  c0 = np.dot(a, b)
  t_delta = time.time() - t0

  print(f'{t_delta :.6f} s')

  print('norm c')
  print(np.linalg.norm(c))
  print('max diff')
  print(np.max(c - c0))

if __name__ == "__main__":

  if len(sys.argv) > 1:
    N = int(sys.argv[1], 10)
    test(N)
  else:
    print(f'usage ./{sys.argv[0]} N')

