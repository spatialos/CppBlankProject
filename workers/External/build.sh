#!/usr/bin/env bash

set -e -u -x -o pipefail

if [[ "$(uname -s)" == "Linux" ]]; then
  cmake .. -DCMAKE_C_FLAGS=-m64 -G "Unix Makefiles"
elif [[ "$(uname -s)" == "Darwin" ]]; then
  cmake .. -DCMAKE_OSX_ARCHITECTURES=x86_64 -G "Unix Makefiles"
else
  cmake .. -DCMAKE_GENERATOR_PLATFORM=x64
fi
