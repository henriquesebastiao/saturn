#!/bin/bash

# Checks if the input file exists
if [ ! -f "src/infrared.h" ]; then
  echo "The file src/infrared.h was not found!"
  exit 1
fi

clang-format --style=gnu src/infrared.h > src/infrared2.h

if [ $? -ne 0 ]; then
  echo "The clang-format command failed!"
  exit 1
fi

mv src/infrared2.h src/infrared.h

echo "The src/infrared.h file was formatted successfully and the temporary file was deleted."
