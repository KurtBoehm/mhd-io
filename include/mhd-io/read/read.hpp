#ifndef INCLUDE_MHD_IO_READ_READ_HPP
#define INCLUDE_MHD_IO_READ_READ_HPP

#include <algorithm>
#include <cassert>
#include <charconv>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "thesauros/containers.hpp"
#include "thesauros/io.hpp"

#include "mhd-io/base.hpp"

namespace mhdio {
inline Value parse_mhd_value(std::string_view sv) {
  auto parse_bool = [](std::string_view s) -> std::optional<bool> {
    if (s == "True") {
      return true;
    }
    if (s == "False") {
      return false;
    }
    return std::nullopt;
  };
  auto parse_int = [](std::string_view s) -> std::optional<Int> {
    Int ret{};
    const auto res = std::from_chars(s.begin(), s.end(), ret);
    if (res.ec == std::errc{} && res.ptr == s.end()) {
      return ret;
    }
    return std::nullopt;
  };
  auto parse_float = [](std::string_view s) -> std::optional<Float> {
    double ret{};
    const auto res = std::from_chars(s.begin(), s.end(), ret);
    if (res.ec == std::errc{} && res.ptr == s.end()) {
      return ret;
    }
    return std::nullopt;
  };

  const char* first_space = std::find(sv.begin(), sv.end(), ' ');
  if (first_space != sv.end()) {
    auto parse = [first_space, sv]<typename T>(T v1, auto parser) {
      std::vector<T> vec{v1};
      for (const char* c = first_space + 1; true;) {
        const char* val_end = std::find(c, sv.end(), ' ');
        assert(val_end != c);
        vec.push_back(parser(std::string_view{c, val_end}).value());
        if (val_end == sv.end()) {
          break;
        }
        c = val_end + 1;
      }
      return vec;
    };

    if (const auto v1 = parse_int({sv.begin(), first_space}); v1.has_value()) {
      return parse(*v1, parse_int);
    }
    if (const auto v1 = parse_float({sv.begin(), first_space}); v1.has_value()) {
      return parse(*v1, parse_float);
    }
    return "space";
  }

  if (const auto v = parse_bool(sv); v.has_value()) {
    return *v;
  }
  if (const auto v = parse_int(sv); v.has_value()) {
    return *v;
  }
  return std::string(sv);
}

inline Map parse_header(std::string_view sv) {
  Map out{};
  for (const char* c = sv.begin(); c != sv.end();) {
    const char* newline = std::find(c, sv.end(), '\n');
    assert(c != newline && newline != sv.end());
    const char* line_end = newline;
    if (*(line_end - 1) == '\r') {
      // Windows line ending
      --line_end;
    }
    assert(c != line_end);
    const char* key_end = std::find(c, line_end, ' ');
    assert(key_end[1] == '=' && key_end[2] == ' ');
    const char* value_start = key_end + 3;

    const std::string_view value(value_start, line_end);
    [[maybe_unused]] const auto inserted =
      out.emplace(std::string(c, key_end), parse_mhd_value(value)).second;
    assert(inserted);
    c = newline + 1;
  }
  return out;
}

inline Map read_mhd(const std::filesystem::path& p) {
  thes::FileReader mhd_reader(p);
  thes::FixedArrayDefault<char> mhd_data(mhd_reader.size());
  mhd_reader.read(mhd_data.data(), mhd_data.size());

  const std::string_view contents(mhd_data.begin(), mhd_data.end());
  return parse_header(contents);
}
} // namespace mhdio

#endif // INCLUDE_MHD_IO_READ_READ_HPP
