#include <iostream>
#include <string>
#include <windows.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


namespace py = pybind11;

// pragma line can be avoided by using link flag
// (cl alert.cpp /link User32.lib)
#pragma comment (lib, "User32.lib")


void alert(){
	MessageBox(NULL, "Alert", "Alert", MB_OK);
}

void alert(const std::string& message){
	MessageBox(NULL, message.c_str(), "Hello", MB_OK);
}

void alert(const std::string& message, const std::string& title){
	MessageBox(NULL, message.c_str(), title.c_str(), MB_OK);
}

PYBIND11_MODULE(winalerts, handle) {
	handle.doc() = "This is the module docs";
	handle.def("alert", py::overload_cast<>(&alert));
	handle.def("alert", py::overload_cast<const std::string&>(&alert));
	handle.def("alert", py::overload_cast<const std::string&, const std::string&>(&alert));
}