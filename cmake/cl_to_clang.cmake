# Set kernel source file from CMake args
set (kernel ${CMAKE_ARGV3})

# Read the OpenCL source file into a variable
file(STRINGS ${kernel} KERNEL_SOURCE NEWLINE_CONSUME)

# Replace newline characters with escape sequences
string(REPLACE "\n" "\\n" KERNEL_SOURCE "${KERNEL_SOURCE}")

# Surround each line in double quotes
string(REPLACE "\\n" "\\n\"\n\"" KERNEL_SOURCE "${KERNEL_SOURCE}")

# Write the OpenCL source to a C source file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/kernel_boost.cl.c "const char *kernel_source = \"" ${KERNEL_SOURCE} "\";\n")