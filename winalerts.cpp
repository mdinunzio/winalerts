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
	const std::string& box_type, const std::string& icon_type){
	
	// Box type
	std::unordered_map<std::string, UINT> box_type_map;
	box_type_map = {
		{"abort_retry_ignore", MB_ABORTRETRYIGNORE},
		{"cancel_continue", MB_CANCELTRYCONTINUE},
		{"help", MB_HELP},
		{"ok", MB_OK},
		{"ok_cancel", MB_OKCANCEL},
		{"retry_cancel", MB_RETRYCANCEL},
		{"yes_no", MB_YESNO},
		{"yes_no_cancel", MB_YESNOCANCEL},
	};
	UINT box_type_int = box_type_map[box_type];

	// Icon type
	std::unordered_map<std::string, UINT> icon_type_map;
	icon_type_map = {
		{"empty", 0},
		{"exclamation", MB_ICONEXCLAMATION},
		{"warning", MB_ICONWARNING},
		{"information", MB_ICONINFORMATION},
		{"asterisk", MB_ICONASTERISK},
		{"question", MB_ICONQUESTION},
		{"stop", MB_ICONSTOP},
		{"error", MB_ICONERROR},
		{"hand", MB_ICONHAND},
	};
	UINT icon_type_int = icon_type_map[icon_type];


	return MessageBox(NULL, message.c_str(), title.c_str(), box_type_int | icon_type_int);
}

PYBIND11_MODULE(winalerts, handle) {
	handle.doc() = "A module for customizable Windows Alerts.";
	handle.def(
		"message_box", &message_box,
		py::arg("message")="Alert",
		py::arg("title")="Alert",
		py::arg("box_type")="ok",
		py::arg("icon_type")="empty");
}