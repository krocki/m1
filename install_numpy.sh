#!/bin/zsh

brew install cython
pip3 install cython --user
git clone git@github.com:numpy/numpy
cd numpy

sudo BLAS=/Users/kamil/git/brew/opt/openblas/lib/libblas.dylib LAPACK=None ATLAS=None python3 setup.py install --user
