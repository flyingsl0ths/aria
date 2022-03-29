#include <iostream>

#include <config.hpp>
#include <core/aria.hpp>

s32 main()
{
	std::cout << ARIA_VERSION_MAJOR << '.' << ARIA_VERSION_MINOR << '.' << ARIA_VERSION_PATCH
			  << '\n';

	auto runner = aria::runner {};

	runner.run();

	return 0;
}
