/*
A module for making alerts and message boxes on Windows.

For more information on Windows alert API see
https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
*/
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
	const std::string& box_type, const std::string& icon_type,
	const int default_button){
	
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

	// Default button
	std::unordered_map<int, UINT> default_button_map;
	default_button_map = {
		{1, MB_DEFBUTTON1},
		{2, MB_DEFBUTTON2},
		{3, MB_DEFBUTTON3},
		{4, MB_DEFBUTTON4},
	};
	UINT default_button_int = default_button_map[default_button];

	return MessageBox(NULL, message.c_str(), title.c_str(),
		box_type_int | icon_type_int | default_button_int);
}

PYBIND11_MODULE(winalerts, handle) {
	handle.doc() = "A module for customizable Windows Alerts.";
	handle.def(
		"message_box", &message_box,
		"Displays a message box to the user.\n\n"
		"Args:\n",
		"\tmessage (str): The message that will appear in the box.\n"
		"\ttitle (str): The text that will appear in the title.\n"
		"\tbox_type (str): The type of box.\n"
		"\t\tOne of:  abort_retry_ignore, cancel_continue, help, "
		"ok, ok_cancel, retry_cancel, yes_no, yes_no_cancel\n"
		"\t\tDefaults to ok.\n"
		"\ticon_type (str): The type of icon displayed.\n"
		"\t\tOne of:  empty, exclamation, warning, information, "
		"asterisk, question, stop, error, hand\n"
		"\t\tDefaults to empty.\n"
		"\tdefault_button (int): The default button, indexed starting at 1.\n"
		"\tDefaults to 1.",
		py::arg("message")="Alert",
		py::arg("title")="Alert",
		py::arg("box_type")="ok",
		py::arg("icon_type")="empty",
		py::arg("default_button")=1);
}