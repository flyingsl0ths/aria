#include <aria/utils/time/time.hpp>

namespace utils::time
{

time_t deltaTime(const time_point_t then, const time_point_t now)
{
	return std::chrono::duration_cast<duration_t>(now - then).count();
}

} // namespace utils::time
