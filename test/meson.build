options_sub = subproject('options')
opts = options_sub.get_variable('all_opts')
args = options_sub.get_variable('all_args')

foreach name : ['UFZ_CT_02.mhd']
  configure_file(copy: true, input: 'data/' + name, output: name)
endforeach

foreach name, deps : {
  'read': [],
}
  test(
    f'test @name@',
    executable(
      f'test-@name@',
      f'@name@.cpp',
      override_options: opts,
      cpp_args: args,
      dependencies: [mhd_io_dep] + deps,
    ),
  )
endforeach
