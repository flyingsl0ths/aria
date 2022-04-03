#pragma once

#include <chrono>

namespace utils::time
{

using timer_t	   = std::chrono::steady_clock;
using time_point_t = timer_t::time_point;
using time_t	   = float;
using duration_t   = std::chrono::duration<time_t>;

time_t deltaTime(time_point_t then, time_point_t now = timer_t::now());

} // namespace utils::time
