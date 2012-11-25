#!/bin/sh
make
rm -fr tmp
mkdir -p tmp/
cp -fr bin images src main.tex Makefile tmp
cd tmp/src
for i in $(ls [0-9]*.tex); do sed -i 's/\\.*//g' $i;	done;
cd ..
make
cp bin/main.pdf ../bin/main_sinchalla.pdf
cd ..
rm -fr tmp
