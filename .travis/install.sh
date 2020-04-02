#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    brew update || brew update
    brew outdated pyenv || brew upgrade pyenv
    brew install pyenv-virtualenv
    brew outdated cmake || brew upgrade cmake
    brew install pip
fi

pip install conan --upgrade
pip install conan_package_tools

conan user

conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
