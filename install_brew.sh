#!/bin/bash
git clone git@github.com:Homebrew/brew
cd brew/bin/
export PATH=${PATH}:${pwd}

brew install tmux
brew install wget
brew install vim
brew install gcc@10
