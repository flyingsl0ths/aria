#pragma once

#include <utils/common.hpp>

namespace aria
{

class runner final
{
  public:
	runner() = default;

	runner(const runner&) = delete;

	runner(runner&&) noexcept(true) = delete;

	~runner() = default;

	runner operator=(const runner&) = delete;

	runner operator=(runner&&) noexcept(true) = delete;

  public:
	void run();
};

} // namespace aria
