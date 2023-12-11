# CMakeList.txt: ���� CMake ��Ŀ�ļ����ڴ˴�ִ��ȫ������
# ����������Ŀ��
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (MeshSimplify)

# ����C++����ѡ��
add_compile_options(-std=c++11)

# ����Eigen��
include_directories(D:/dev/eigen-3.3.9)

# ����Libigl��
include_directories(D:/dev/libigl/include)

# �������Դ�����ļ�
set(SOURCES
     src/main.cpp
     src/simplification.cpp
     src/Edge.cpp
     src/EdgeHeap.cpp
)

set(HEADERS
     src/BasicDataType.h
     src/simplification.h
     src/Edge.h
     src/EdgeHeap.h
)

add_executable(MeshSimplify ${SOURCES} ${HEADERS})

target_link_libraries(MeshSimplify ${GMP_LIBRARIES})

