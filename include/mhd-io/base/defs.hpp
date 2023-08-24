#ifndef INCLUDE_MHD_IO_BASE_DEFS_HPP
#define INCLUDE_MHD_IO_BASE_DEFS_HPP

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

#include "ankerl/unordered_dense.h"

namespace mhdio {
using Int = std::int64_t;
using Float = double;

using Ints = std::vector<Int>;
using Floats = std::vector<Float>;

using Value = std::variant<bool, Int, Ints, Floats, std::string>;
using Map = ankerl::unordered_dense::map<std::string, Value>;
} // namespace mhdio

#endif // INCLUDE_MHD_IO_BASE_DEFS_HPP
