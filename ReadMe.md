# MHD I/O 🗄️: MetaImage Headers Parsing

MHD I/O is a header-only C++20 library which provides utilities to parse a [MetaImage Header](https://insightsoftwareconsortium.github.io/ITKWikiArchive/Wiki/ITK/MetaIO/Documentation/) and represents it as an [`ankerl::unordered_dense::map`](https://github.com/martinus/unordered_dense/) with `std::variant`-based values.

## Building

MHD I/O uses the Meson build system and includes a fairly extensive set of tests.
These can be run by executing `meson setup -C <build directory>` followed by `meson test -C <build directory>`.

## Dependencies

Dependencies are handled using Meson subprojects, which make it possible to use MHD I/O without installing any packages.
The Meson subprojects are managed by [Tlaxcaltin](https://github.com/KurtBoehm/tlaxcaltin) and are only [Thesauros](https://github.com/KurtBoehm/thesauros) and [`ankerl::unordered_dense::{map, set}`](https://github.com/martinus/unordered_dense), in addition to the compiler options defined in Tlaxcaltin.

## Licences

MHD I/O is licenced under the terms of the Mozilla Public Licence 2.0, which is provided in [`License`](License).
