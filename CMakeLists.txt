cmake_minimum_required(VERSION 3.20)
project(MyProject)

# 包含全局优化配置
include(cmake/AutoOptimize.cmake)

# 自动包含所有子目录（包括未来新建的）
file(GLOB_RECURSE SUBDIRS "src/*/CMakeLists.txt")
foreach(subdir ${SUBDIRS})
    get_filename_component(dir ${subdir} DIRECTORY)
    add_subdirectory(${dir})
endforeach()
# ...existing code...
add_executable(hello hello.cpp)
# ...existing code...