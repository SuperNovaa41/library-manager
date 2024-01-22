#!/bin/sh



make

cd bin/

wget https://github.com/SuperNovaa41/isbn-lookup/releases/download/release/isbn
chmod +x isbn

cd ..

npm install # setup NPM depedencies

npm run tauri dev
