# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.25)

# 设置项目名称和版本
project(DebugProject  C CXX)

# 设置 C++ 标准
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

#设置C标准
set(CMAKE_C_STANDARD 11)

# 添加可执行文件
add_executable(Debug main.c)

# 添加库
#dd_library(MyMath STATIC src/mymath.cpp include/mymath.h)

# 包含头文件目录
#target_include_directories(MyMath PUBLIC include)
#target_include_directories(MyApp PRIVATE include)

# 链接库到可执行文件
#target_link_libraries(Debug PRIVATE MyMath)

# 安装规则（可选）
#install(TARGETS MyApp DESTINATION bin)
#install(TARGETS MyMath DESTINATION lib)
#install(FILES include/mymath.h DESTINATION include)