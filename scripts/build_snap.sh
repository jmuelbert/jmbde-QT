#!/bin/bash

set -e
echo "$@"

# Get actual snapimage
docker pull snapcore/snapcraft:stable

# Build the snap
docker run -v "$PWD":/build -w /build snapcore/snapcraft:stable snapcraft
