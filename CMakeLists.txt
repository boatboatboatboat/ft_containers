cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_FLAGS "-fsanitize=address -O0 -g3 -Wall -Wextra -Werror")
set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers main.cpp vector.hpp iterator/iterator.hpp iterator/iterator.ipp helpers/enable_if.hpp helpers/is_iterator.hpp helpers/iterator_tags.hpp  stack.hpp helpers/diff_input_iterator.hpp helpers/hacks.hpp helpers/type_dereference.hpp)