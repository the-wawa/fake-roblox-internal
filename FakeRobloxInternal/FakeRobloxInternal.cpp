#include <Windows.h>
#include <thread>
#include <chrono>

#define DEBUG false
#if DEBUG == true
#include <stdio.h>
#define ok(msg, ...) printf("[+] " msg, __VA_ARGS__)
#define warn(msg, ...) printf("[-] " msg, __VA_ARGS__)
#define info(msg, ...) printf("[*] " msg, __VA_ARGS__)
#else
#define ok(msg, ...)
#define warn(msg, ...)
#define info(msg, ...)
#endif

int main()
{
#if DEBUG != true
	FreeConsole();
#endif
	ok("waiting for Roblox to open\n");
	HWND window = NULL;
	do
	{
		window = FindWindowW(NULL, L"Roblox");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (!window);

	ok("found Roblox window! waiting for the window to become visible\n");
	while (!IsWindowVisible(window))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	while (!SetWindowTextW(window, L"Roblox (Internal)"))
	{
		warn("unable to set window title! error <%ld>\n", GetLastError());
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return EXIT_SUCCESS;
}