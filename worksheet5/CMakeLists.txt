# 1. 必须是第一行：指定最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 必须紧随其后：定义项目名称
project(Worksheet5)

# 3. 设置 CPack 安装包生成器 [cite: 223-228]
if (WIN32)
    set (CPACK_GENERATOR "NSIS")  # Windows 环境下使用 NSIS 创建安装程序 [cite: 224]
else ()
    set (CPACK_GENERATOR "ZIP")   # 其他环境下使用 ZIP 压缩包 [cite: 227]
endif ()

# 4. 包含 CPack 模块 [cite: 230]
include (CPack)

# 5. 定义生成目标（必须放在 install 命令之前！） [cite: 232-235]
# 先创建库和可执行文件，这样下方的 install 才能找到它们 [cite: 232, 234]
add_library (maths adder.cpp)
add_executable (calc calc.cpp)
target_link_libraries (calc maths)

# 6. 配置安装路径 [cite: 236-241]
# 告诉 CMake 将生成的文件存放在安装目录的哪个子文件夹中 [cite: 244]
install (TARGETS calc maths
    RUNTIME DESTINATION bin         # .exe 文件存放在 bin 目录 [cite: 239, 245]
    LIBRARY DESTINATION lib         # 库文件存放在 lib 目录 [cite: 240, 245]
    ARCHIVE DESTINATION lib/static  # 静态库文件存放在 lib/static 目录 [cite: 241]
)