#pragma once

#include <type_traits>

namespace utils::types
{

template <typename T>
using remove_cvr_t = std::remove_cv_t<std::remove_reference_t<T>>;

} // namespace utils::types
