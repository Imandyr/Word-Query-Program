#!/bin/bash
# Build main.cpp using GCC, writing into "main".
pp="$(dirname "${0}")/main"
g++ "${pp}.cpp" -rdynamic -Og -o "${pp}"
