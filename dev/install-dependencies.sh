#!/bin/sh

cd ../

mkdir -p bin
cd bin

wget https://github.com/SuperNovaa41/isbn-lookup/releases/download/0.0.3/isbn
chmod +x isbn

cd ../

npm install

cd dev/
