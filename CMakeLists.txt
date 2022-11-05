cmake_minimum_required(VERSION 3.16)
project(thread_safe_stack)

set(CMAKE_CXX_STANDARD 17)

add_executable(thread_safe_stack main.cpp threadsafe_stack.h)
target_link_libraries(thread_safe_stack pthread)
