#!/bin/bash

# This script will generate .qrc file from used icons.
#
# PWD is used as used src root folder.
# "resources/graphics/Papirus" is used as folder for icons.
# Output qrc file has paths relative to "resources" folder.

echo_formatted_qrc() {
  printf "<RCC>\n  <qresource prefix=\"/\">\n"
  
  # Sort icons first.
  readarray -t sorted < <(for a in "$@"; do echo "$a"; done | sort)
  
  for ICON_FILE in "${sorted[@]}"; do
    # We find icon.
    echo "    <file>$ICON_FILE</file>"
  done
  
  printf "  </qresource>\n</RCC>"
}