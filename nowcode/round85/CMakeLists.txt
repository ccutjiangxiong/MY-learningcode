cmake_minimum_required(VERSION 3.20)
get_filename_component(PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

# 指定使用 clang-cl 编译器
set(CMAKE_C_COMPILER "clang-cl")
set(CMAKE_CXX_COMPILER "clang-cl")

# 设置 MSVC 模式
set(CMAKE_C_COMPILER_FRONTEND_VARIANT "MSVC")
set(CMAKE_CXX_COMPILER_FRONTEND_VARIANT "MSVC")

# 设置默认构建类型为 Release
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")

# 清空默认编译选项
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_RELEASE "")

# 启用 Unity Build
set(CMAKE_UNITY_BUILD ON)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 16)

# 启用 ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# 链接器优化选项
set(CMAKE_EXE_LINKER_FLAGS "/INCREMENTAL /OPT:NOREF /OPT:NOICF /subsystem:console")

# 使用 lld-link
set(CMAKE_LINKER "lld-link")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=lld /std:c++20 /MP /W0 /Z0 /EHsc /MD /O0 /DNDEBUG /nologo")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 清空旧的映射文件
file(WRITE "${CMAKE_BINARY_DIR}/target_map.txt" "")

function(add_named_executable source)
    get_filename_component(filename ${source} NAME_WE)
    file(SHA1 ${source} name_hash)
    string(SUBSTRING ${name_hash} 0 8 short_hash)
    set(target_name "run_${short_hash}")
    
    add_executable(${target_name} ${source})
    set_target_properties(${target_name} PROPERTIES 
        OUTPUT_NAME "${filename}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )
    set_target_properties(${target_name} PROPERTIES UNITY_BUILD ON)
    file(APPEND "${CMAKE_BINARY_DIR}/target_map.txt"
        "${filename}=${target_name}\n"
    )
endfunction()

file(GLOB SOURCES "*.cpp")
foreach(source ${SOURCES})
    add_named_executable(${source})
endforeach()