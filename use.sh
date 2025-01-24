#!/bin/bash
# An example of how to use the built program.
pp="$(dirname "${0}")"
eval "\"${pp}\"/bin/main \"${pp}\"/text.txt something"
