#!/bin/bash

set -e
echo "$@"

# Get actual flatpakimage

docker pull freedesktopsdk/flatpak:20.08-x86_64

# Build the snap
docker run -v "$PWD":/build -w /build freedesktopsdk/flatpak:20.08-x86_64 apt-get -y -qq update
docker run -v "$PWD":/build -w /build freedesktopsdk/flatpak:20.08-x86_64 apt-get install -y flatpak flatpak-builder
docker run -v "$PWD":/build -w /build freedesktopsdk/flatpak:20.08-x86_64 flakpak
