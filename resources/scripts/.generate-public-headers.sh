#!/bin/bash

# Call from repository root folder.
root=$(pwd)
lib_root=$root/src

cd "$lib_root"

for header in $(find ???/x -name *.h); do
  echo "../$header \\"
done

cd "$root"