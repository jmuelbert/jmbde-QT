#!/bin/bash

# Call from repository root folder.
root=$(pwd)
lib_root=$root/src

cd "$lib_root"

for header in $(find libjmbde/ -name *.h); do
  echo "../$header \\"
done

cd "$root"