# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (MeshSimplify)

# 添加C++编译选项
add_compile_options(-std=c++11)

# 查找Eigen库
include_directories(D:/dev/eigen-3.3.9)

# 查找Libigl库
include_directories(D:/dev/libigl/include)

find_package(OpenMP REQUIRED)
# 添加你的源代码文件
set(SOURCES
     src/main.cpp
     src/BaseModel.cpp
     src/Vertex.cpp
     src/Edge.cpp
     src/Heap.cpp
     src/Simplification.cpp
)

set(HEADERS
     src/BasicDataType.h
     src/BaseModel.h
     src/Vertex.h
     src/Edge.h
     src/Heap.h
     src/Simplification.h
)

add_executable(MeshSimplify ${SOURCES} ${HEADERS})

target_link_libraries(MeshSimplify 
  PUBLIC
    OpenMP::OpenMP_CXX
)


