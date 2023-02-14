project(
  'BMPImageLibrary',
  'c',
  version : '0.1',
  default_options: [
    'warning_level=3',
    'werror=true',
    'buildtype=debug',
    'debug=true',
    'c_std=c18'
  ]
)

LIB_SRC = [
  'src/bmp.c'
]

BPM = library(
          'bpm',
          LIB_SRC, 
          install : true,
          # include_directories: INC,
          # dependencies: DEPS,
)

loader = executable(
  'loader',
  'tests/bpm.c',
  link_with: [
    BPM
    ]
)
