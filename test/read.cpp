#include <filesystem>
#include <iostream>
#include <variant>

#include "mhd-io/read.hpp"

int main(int /*argc*/, const char* const* const argv) {
  const auto base_path = std::filesystem::canonical(std::filesystem::path{argv[0]}.parent_path());
  const auto mhd_path = base_path / "UFZ_CT_02.mhd";

  for (const auto& [key, value] : mhdio::read_mhd(mhd_path)) {
    std::cout << key << ": ";
    std::visit([](const auto& v) { std::cout << thes::print(v) << '\n'; }, value);
  }
}
