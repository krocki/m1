#!/bin/zsh
git clone git@github.com:vim/vim
cd vim
./configure
make -j4
make install
