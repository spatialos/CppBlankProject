#!/usr/bin/env bash

set -e -u -x -o pipefail

cd "$(dirname "$0")/.."

spatial build --log_level=debug
