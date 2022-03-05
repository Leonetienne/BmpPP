#!/bin/bash

# Replace {PROJECT_NAME} with first parameter given in all files
find . -type f -exec sed -i "s/{PROJECT_NAME}/$1/g" {} \;

