#!/bin/bash
set -eo pipefail
set -x

# Don't follow links
# shellcheck disable=SC1091
. ./rtapi.conf

if [ "$RTPREFIX" != uspace ]; then
    echo "test only meaningful on uspace"
    exit 0
fi

${SUDO} halcompile --install test_uspace_spawnv.c
halrun test_uspace_spawnv.hal
