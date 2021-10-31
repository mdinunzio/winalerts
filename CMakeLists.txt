cmake_minimum_required(VERSION 3.4)
project(winalerts)
add_subdirectory(pybind11)
pybind11_add_module(winalerts winalerts.cpp)