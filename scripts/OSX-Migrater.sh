#!/usr/bin/env bash

# A qTox profile migrater for OSX
now=$(date +"%m_%d_%Y-%H.%M.%S")
bak="jmbde-Backup-$now"
mkdir ~/Projects/"${bak}"

echo "Figuring out if action is required ..."
if [ -f ~/Library/Preferences/io.github.jmuelbert.jmbde.plist ]; then
    echo "Moving settings ..."
    mv ~/Library/Preferences/io.github.jmuelbert.jmbde.plist ~/Projects/"${bak}"
    echo "Done! You profile(s) have been moved! A back up coppy still exists at:"
    echo "$bak"
else
    echo "Cannot locate old profile directory, profile migration not performed"
fi
if [ -d ~/Library/Application\ Support/io.github.jmuelbert.jmbde ]; then
    echo "Moving the DB ..."
    mv ~/Library/Application\ Support/io.github.jmuelbert.jmbde ~/Projects/"${bak}"
    echo "Done! You profile(s) have been moved! A back up coppy still exists at:"
    echo "$bak"
else
    echo "Cannot locate old database, profile migration not performed"
fi
exit 0
