project(
  'Zane',
  'cpp',
  version: '1.0.0',
  default_options: [
    'cpp_std=c++23',
    'warning_level=2',
    'buildtype=release',
  ],
)

python = import('python').find_installation()

coda_inc = include_directories('vendor/coda/include')                      
coda_dep = declare_dependency(include_directories: coda_inc)               

antlr4_dep = dependency(
  'antlr4-runtime',
  required: true,
  method: 'cmake',
  modules: ['antlr4_static'],
)
nlohmann_dep = dependency('nlohmann_json', required: true, method: 'cmake')
cereal_dep = dependency('cereal', required: true, method: 'cmake')

llvm_modules = [
  'core',
  'orcjit',
  'executionengine',
  'support',
  'x86codegen',
  'x86asmparser',
  'x86desc',
  'x86disassembler',
  'x86info',
  'aarch64codegen',
  'aarch64asmparser',
  'aarch64desc',
  'aarch64disassembler',
  'aarch64info',
  'aarch64utils',
  'windowsdriver',
]

llvm_dep = dependency(
  'llvm',
  modules: llvm_modules,
  method: 'config-tool',
  required: true,
)

src_dir = include_directories('src')
generated_dir = include_directories('generated-parser')

buildtype = get_option('buildtype')
is_debug = buildtype.startswith('debug')

parser_cpp_args = []
exe_cpp_args = []
exe_link_args = []

if is_debug
  parser_cpp_args += ['-O1', '-g']
  exe_cpp_args += ['-O1', '-g', '-fsanitize=address,undefined', '-fstack-protector-strong']
  exe_link_args += ['-fsanitize=address,undefined']
else
  parser_cpp_args += ['-O3', '-flto', '-fvisibility=hidden']
  exe_cpp_args += ['-O3', '-march=native', '-flto', '-fvisibility=hidden']
  exe_link_args += ['-flto', '-Wl,--strip-all', '-Wl,--gc-sections']
endif

embedded_types_header = custom_target(
  'embedded_types',
  output: 'embedded_types.hpp',
  command: [python, files('scripts/embed_data.py')],
  depend_files: [
    files('data/types.csv'),
    files('data/builtins.csv'),
  ],
  build_by_default: true,
)

parser_sources = run_command(
  'find', 'generated-parser/parser', '-name', '*.cpp', check: true
).stdout().strip().split('\n')

parser_lib = static_library(
  'zane_parser',
  parser_sources,
  include_directories: [generated_dir, src_dir],
  dependencies: [antlr4_dep],
  cpp_args: parser_cpp_args,
  build_by_default: true,
)

sources = run_command(
  'find', 'src', '-name', '*.cpp', check: true
).stdout().strip().split('\n')

zane_exe = executable(
  meson.project_name(),
  sources + [embedded_types_header],
  include_directories: [src_dir, generated_dir],
  dependencies: [nlohmann_dep, cereal_dep, antlr4_dep, llvm_dep, coda_dep],
  link_with: [parser_lib],
  build_by_default: true,
  cpp_args: exe_cpp_args,
  link_args: exe_link_args,
)

upx = find_program('upx', required: false)
if upx.found() and buildtype == 'release'
  upx_target = custom_target(
    'upx_pack',
    output: 'upx_pack.stamp',
    command: [python, files('scripts/upx_pack.py'), upx, zane_exe.full_path(), '@OUTPUT@'],
    depends: zane_exe,
    build_by_default: true,
  )
endif
