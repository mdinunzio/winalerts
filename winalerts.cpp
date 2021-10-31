#include <iostream>
#include <string>
#include <windows.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


namespace py = pybind11;

// pragma line can be avoided by using link flag
// (cl alert.cpp /link User32.lib)
#pragma comment (lib, "User32.lib")


void alertbox(){
	MessageBox(NULL, "Alert", "Alert", MB_OK);
}

void alertbox(const std::string& message){
	MessageBox(NULL, message.c_str(), "Hello", MB_OK);
}

PYBIND11_MODULE(winalerts, handle) {
	handle.doc() = "This is the module docs";
	handle.def("alertbox", py::overload_cast<>(&alertbox));
	handle.def("alertbox", py::overload_cast<const std::string&>(&alertbox));
}