#!/bin/bash

# This script will pull Flathub/jmbde repo
# and push new appdata/flatpak-json to new branch.
echo "flathub"

commit_hash=$2
tag=$1
json_file="io.github.jmuelbert.jmbde-QT.json"
json_file_new="${json_file}.new"

git clone https://jmuelbert:${GH_TOKEN}@github.com/flathub/io.github.jmuelbert.jmbde-QT.git ./flathub
cd flathub

# Remove branch and create new one.
git push -d origin new-version
git branch -D new-version
git checkout -b new-version

# Replace old commit hash and branch.
cat "$json_file" | sed -e "s@\"branch\": \".*\"@\"branch\": \"$tag\"@g" > "$json_file_new"
cat "$json_file_new" | sed -e "s@\"commit\": \".*\"@\"commit\": \"$commit_hash\"@g" > "$json_file"

cat "$json_file"

git commit -a -m "New version for commit $commit_hash."
git push origin new-version -f