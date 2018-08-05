# hacking python27

深入学习Python27源码

## 目录结构

- `Objects`：该目录包含了所有Python的内建对象，包括整数、list、dict等。同时，还包括了Python在运行时所需要的所有内部使用对象的实现。
- `Parser`：该目录包含了Python解释器中的Scanner和Parser部分，即对Python源代码进行词法分析和语法分析的部分。除了这些，Parser目录下还包含了一些有用的工具，这些工具能够根据Python语言的语法自动生成Python语言的词法和语法分析器。
- `Python`：该目录下包含了Python解释器中的Compiler和执行引擎部分，是Python运行的核心所在。
- `PCBuild`：包含了VS的工程文件。

