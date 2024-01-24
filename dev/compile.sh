#!/bin/sh

./install-dependencies.sh

cd ../

make

npm run tauri dev
