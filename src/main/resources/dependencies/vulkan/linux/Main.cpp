#include <thread>

#ifndef _FUZZER_COMPUTE_ONLY_
#include "AppWindow.hpp"
#endif

#include "WindowConfig.hpp"
#include "ExitCondition.hpp"

#define WIDTH 640
#define HEIGHT 480

using namespace fuzzer;

// Function declarations
void fuzz(const ExitConditionPtr &exitCondition,
		const display::WindowConfigPtr &config);

int main(int argc, char *argv[])
{
    // Initial setup
	ExitConditionPtr exitCondition = std::make_shared<ExitCondition>();
	display::WindowConfigPtr config = std::make_shared<display::WindowConfig>(WIDTH, HEIGHT);

#ifndef _FUZZER_COMPUTE_ONLY_
	display::AppWindowPtr window =
			std::unique_ptr<display::AppWindow>(new display::AppWindow(config));
#endif

	// Start fuzzer in a thread of its own
	std::thread fuzzer(fuzz, std::ref(exitCondition), std::ref(config));

#ifndef _FUZZER_COMPUTE_ONLY_
	// Loop until fuzzer is finished
	window->showAndloopForEver(exitCondition);
#endif

	// Make sure the fuzzer thread exits first before returning
	if (fuzzer.joinable())
	{
		fuzzer.join();
	}

    return 0;
}
