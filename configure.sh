#!/bin/bash

# Replace {PROJECT_NAME} with first parameter given in all files
find . -type f -not \( -path '*.git/*' -or -path '*configure.sh*' -or -name 'Catch2.h' \) -exec sed -i "s/{PROJECT_NAME}/$1/g" {} \;

