# Method A (easiest)

### Install Homebrew
```
git clone git@github.com:Homebrew/brew
cd brew/bin/
echo 'export PATH="$PWD:$PATH"' >> ~/.zshrc
source ~/.zshrc
```
### Install OpenBLAS

```
brew install openblas
```

### Install NumPy
```
# install pip
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py
# numpy
OPENBLAS="$(brew --prefix openblas)" pip3 install numpy
```




# Method B
```
git clone git@github.com:xianyi/OpenBLAS.git
cd OpenBLAS
make CC=gcc FC=fc CXX=g++
sudo make PREFIX=/opt/OpenBLAS install
```

# Cython

```
brew install cython
pip3 install cython --user
git clone git@github.com:numpy/numpy
cd numpy

```

### numpy without extras
```
BLAS=None LAPACK=None ATLAS=None python3 setup.py install --user
```

### numpy with blas
```
sudo BLAS=/Users/kamil/git/brew/opt/openblas/lib/libblas.dylib LAPACK=None ATLAS=None python3 setup.py install --user
```

