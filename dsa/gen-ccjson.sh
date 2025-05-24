#!/bin/bash
PROJECT_ROOT=$(pwd)

echo "[" > compile_commands.json

for src in $(find src -name "*.c"); do
  obj="build/$(basename ${src} .c).o"
  echo "  {" >> compile_commands.json
  echo "    \"directory\": \"$PROJECT_ROOT\"," >> compile_commands.json
  echo "    \"command\": \"gcc -Wall -Wextra -g -Iinclude -c $src -o $obj\"," >> compile_commands.json
  echo "    \"file\": \"$PROJECT_ROOT/$src\"" >> compile_commands.json
  echo "  }," >> compile_commands.json
done

truncate -s-2 compile_commands.json
echo -e "\n]" >> compile_commands.json

