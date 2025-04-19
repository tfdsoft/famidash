#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

echo Exporting everything specified in metadata.json5
python3 ${SCRIPT_DIR}/export_wrapper.py "$@"

echo Export finished.

