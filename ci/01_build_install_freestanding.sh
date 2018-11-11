#!/bin/bash -x
set -o errexit

# check existance and print version
which flex
flex --version

# check existance and print version
which bison
bison --version

target="powerpc-eabi"

prefix="$PWD/install"

export PATH="$prefix/bin:$PATH"

config_options_gcc="
--enable-languages=c,c++
--disable-shared
--enable-lto
--with-float=soft
--without-headers
--disable-threads
--disable-decimal-float
--disable-multilib
--disable-nls
--disable-libstdcxx
--disable-libgomp
--disable-libvtv
--disable-libatomic
--disable-libmpx
--disable-libquadmath
--disable-libssp
"

mkdir -p build_gcc
cd build_gcc

../gcc/configure --prefix="$prefix" --target="$target" ${config_options_gcc}
make -j$(nproc) all-gcc
make -j$(nproc) all-target-libgcc
make install-gcc
make install-target-libgcc

cd ..
