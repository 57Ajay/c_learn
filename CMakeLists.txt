cmake_minimum_required(VERSION 3.20)

# Project name
project(c_learn)

# Set the C standard
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Enable compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include the headers
include_directories(include)

# Add the executable
add_executable(${PROJECT_NAME} 
  src/main.c
  src/more.c
  src/files.c
  src/structs.c
  src/memMngmnt.c
)

# Set output directory
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
