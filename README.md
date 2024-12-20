# ceditor

ceditor 是一个基于 C++ 的简易 Windows 终端文本编辑器，它提供了一个基本的文本编辑环境，支持语法高亮、文本导航、编辑操作等功能。

## 项目结构

项目包含以下主要组件和目录：

- `components`: 包含编辑器的主要组件，如编辑器、文本区域、光标等。
- `data`: 包含语法高亮的规则和数据。
- `mystl`: 包含自定义的 STL 容器实现，如向量、列表、双端队列等。
- `utils`: 包含一些实用工具，如动作管理器、语法分析器等。
- `main.cpp`: 编辑器的主入口文件。
- `CMakeLists.txt` 和 `Makefile`: 用于项目的编译和构建。

## 编译

项目使用 CMake 和 Makefile 进行编译。在项目根目录下，你可以使用以下步骤来编译项目：

1. 将 [Google Test](https://github.com/google/googletest) 库添加到项目的 test 目录中。

2. 创建 `build` 目录。

    ```bash
    mkdir build
    ```

3. 在根目录下运行以下命令：

    ```bash
    cmake -G "Unix Makefiles" -S . -B build
    make -C build
    ```

编译完成后，可执行文件将位于 `build` 目录下。

## 使用

运行编辑器：

```bash
./ceditor [file]
```

其中 `[file]` 是需要编辑的文件路径。

在编辑器中，你可以使用以下按键来进行基本的编辑操作：

- `i`: 进入插入模式。
- `ESC`: 退出插入模式/退出编辑器。
- 方向键：在文本中导航。

编辑模式下，可以使用`Ctrl+Z`和`Ctrl+Y`进行撤销和重做操作。

## 联系方式

如有任何问题或建议，请通过项目的 Issue 跟踪器提交。

## 许可证

本项目使用 MIT 许可证。有关详细信息，请参阅 LICENSE 文件。
