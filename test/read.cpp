#include <filesystem>
#include <iostream>
#include <variant>
#include <vector>

#include "mhd-io/base.hpp"
#include "thesauros/test.hpp"

#include "mhd-io/read.hpp"

int main(int /*argc*/, const char* const* const argv) {
  using namespace std::literals;

  const auto base_path = std::filesystem::canonical(std::filesystem::path{argv[0]}.parent_path());
  const auto mhd_path = base_path / "UFZ_CT_02.mhd";

  auto header = mhdio::read_mhd(mhd_path);
  for (const auto& [key, value] : header) {
    std::cout << key << ": ";
    std::visit([](const auto& v) { std::cout << thes::print(v) << '\n'; }, value);
  }

  THES_ASSERT(header["NDims"] == mhdio::Value{3});
  THES_ASSERT(header["DimSize"] == (mhdio::Value{std::vector<mhdio::Int>{510, 510, 483}}));
  THES_ASSERT(header["ElementType"] == mhdio::Value{"MET_UCHAR"});
  THES_ASSERT(header["ElementDataFile"] == mhdio::Value{"UFZ_CT_02.raw"});
}
