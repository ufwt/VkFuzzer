#include <thread>

#include "stdafx.h"
#include "WindowConfig.hpp"
#include "ExitCondition.hpp"

#ifndef _FUZZER_COMPUTE_ONLY_
#include "AppWindow.hpp"
#endif

#define WIDTH 640
#define HEIGHT 480

using namespace fuzzer;

// Function declarations
void fuzz(const ExitConditionPtr &exitCondition,
		const display::WindowConfigPtr &config);


#ifndef _FUZZER_COMPUTE_ONLY_
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// Initial setup
	ExitConditionPtr exitCondition = std::make_shared<ExitCondition>();
	display::WindowConfigPtr config =
			std::make_shared<display::WindowConfig>(nCmdShow, WIDTH, HEIGHT, hInstance);

	display::AppWindowPtr window =
			std::unique_ptr<display::AppWindow>(new display::AppWindow(config));

	// Start fuzzer in a thread of its own
	std::thread fuzzer(fuzz, std::ref(exitCondition), std::ref(config));

	// Loop until fuzzer is finished
	window->showAndloopForEver(exitCondition);

	// Make sure the fuzzer thread exits first before returning
	if (fuzzer.joinable())
	{
		fuzzer.join();
	}

	return 0;
}
#else // _FUZZER_COMPUTE_ONLY_
int main(int argc, char *argv[])
{
	// Initial setup
	ExitConditionPtr exitCondition = std::make_shared<ExitCondition>();
	display::WindowConfigPtr config = nullptr;

	// Start fuzzer in a thread of its own
	std::thread fuzzer(fuzz, std::ref(exitCondition), std::ref(config));

	// Make sure the fuzzer thread exits first before returning
	if (fuzzer.joinable())
	{
		fuzzer.join();
	}

	return 0;
}
#endif // _FUZZER_COMPUTE_ONLY_