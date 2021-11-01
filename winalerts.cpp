#include <iostream>
#include <string>
#include <windows.h>
#include <unordered_map>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


namespace py = pybind11;

// pragma line can be avoided by using link flag
// (cl alert.cpp /link User32.lib)
#pragma comment (lib, "User32.lib")


int message_box(const std::string& message, const std::string& title,
	const std::string& box_type){
	
	std::unordered_map<std::string, UINT> box_type_map;
	box_type_map = {
		{"MB_ABORTRETRYIGNORE", MB_ABORTRETRYIGNORE},
		{"MB_CANCELTRYCONTINUE", MB_CANCELTRYCONTINUE},
		{"MB_HELP", MB_HELP},
		{"MB_OK", MB_OK},
		{"MB_OKCANCEL", MB_OKCANCEL},
		{"MB_RETRYCANCEL", MB_RETRYCANCEL},
		{"MB_YESNO", MB_YESNO},
		{"MB_YESNOCANCEL", MB_YESNOCANCEL},
	};
	UINT box_type_int = box_type_map[box_type];
	
	return MessageBox(NULL, message.c_str(), title.c_str(), box_type_int);
}

PYBIND11_MODULE(winalerts, handle) {
	handle.doc() = "A module for customizable Windows Alerts.";
	handle.def(
		"message_box", &message_box,
		py::arg("message")="Alert",
		py::arg("title")="Alert",
		py::arg("box_type")="MB_OK");
}