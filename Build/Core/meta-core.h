#pragma once

#include <iostream>
#include <concepts>
#include <Windows.h>
#include <type_traits>
#include <cassert>

//Make sure that all classes or struct that uses virtual memory inherits from this struct
struct virtual_memory {};

//make sure that all template arguments of virtual_object inherits from virtual_memory
template<typename T>
concept virtual_object = std::is_base_of<virtual_memory, T>::value;


