project('mhd-io', 'cpp', default_options: ['cpp_std=c++20', 'warning_level=3'])

thesauros_dep = dependency('thesauros')
unordered_dense_dep = dependency('unordered_dense')

mhd_io_dep = declare_dependency(
  include_directories: include_directories('include'),
  dependencies: [thesauros_dep, unordered_dense_dep],
)

install_subdir(
  'include',
  install_dir: 'include',
)

pc = import('pkgconfig')
pc.generate(
  name: 'mhd-io',
  version: meson.project_version(),
  description: 'A MetaImage header I/O library',
)

if get_option('test')
  subdir('test')
endif
