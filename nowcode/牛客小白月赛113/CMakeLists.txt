cmake_minimum_required(VERSION 3.12)
project("my_project")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 启用 Unity Build
set(CMAKE_UNITY_BUILD ON)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 16)

# 启用 ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=lld /std:c++20 /MP /W0  /EHsc -O0 /DNDEBUG /nologo -nostdlib++")
# 链接器优化选项
set(CMAKE_EXE_LINKER_FLAGS "/INCREMENTAL /OPT:NOREF /OPT:NOICF /subsystem:console")

# 使用 lld-link
set(CMAKE_LINKER "lld-link")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 清空旧的映射文件（关键！）
file(WRITE "${CMAKE_BINARY_DIR}/target_map.txt" "")

function(add_named_executable source)
    get_filename_component(filename ${source} NAME_WE)
    file(SHA1 ${source} name_hash)  # 改用文件内容哈希
    string(SUBSTRING ${name_hash} 0 8 short_hash)
    set(target_name "run_${short_hash}")
    
    add_executable(${target_name} ${source})
    set_target_properties(${target_name} PROPERTIES 
        OUTPUT_NAME "${filename}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )
    
    # 追加写入映射文件（关键修改！）
    file(APPEND "${CMAKE_BINARY_DIR}/target_map.txt"
        "${filename}=${target_name}\n"
    )
endfunction()

file(GLOB SOURCES "*.cpp")
foreach(source ${SOURCES})
    add_named_executable(${source})
endforeach()

# 构建后验证（调试用）
execute_process(
    COMMAND ${CMAKE_COMMAND} -E echo "Generated target_map:"
    COMMAND ${CMAKE_COMMAND} -E cat "${CMAKE_BINARY_DIR}/target_map.txt"
)