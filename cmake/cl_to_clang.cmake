set (kernel ${CMAKE_ARGV3})
file(STRINGS ${kernel} kernel_content NEWLINE_CONSUME)
string(REGEX REPLACE "([^\n]+)" [["\1 "]] kernel_content "${kernel_content}")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/kernel_boost.cl.c "const char *source_str = " ${kernel_content} ";")