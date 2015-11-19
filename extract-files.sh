#!/bin/sh

set -e

export VENDOR=samsung
export DEVICE=tbltexx
./../../$VENDOR/tblte-common/extract-files.sh $@
