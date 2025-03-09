project(
    'restoran pak amba',
    'cpp',
    default_options: ['warning_level=3', 'cpp_std=c++14'],
)

incdir = include_directories('include')
src = [
    'src/utils.cpp',
    'src/doubly_linked.list.cpp',
    'src/queue.cpp',
    'src/fileio.cpp',
    'src/main.cpp',
    'src/admin.cpp',
    'src/cashier.cpp',
    'src/user.cpp',
]

executable('main', src, include_directories: incdir)
