#!/usr/bin/env bash
doxygen Doxyfile html
if [[ -x $(which http-server) ]]; then
    http-server docs/html
fi
