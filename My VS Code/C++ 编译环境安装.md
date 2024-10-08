# 1 必备插件

**注意！要编译 C++ 必须有 mingw 安装包，其安装过程我就不赘述了。** 下载网址：[MinGW-w64 - for 32 and 64 bit Windows Files](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/)。

红框中的四个插件是必备的，安装后可通过上方的 *Run* 运行或调试代码。

![image](https://github.com/user-attachments/assets/bfd25a75-90eb-4cf3-b4c1-1a63754ce3df)

# 2 `.json` 文件配置

在下述的配置文件中，请将所有的路径请参照自己 mingw 安装的路径进行修改。

这里的 json 文件只是作为我个人的配置，仅供参考使用，并不能适用所有工程。而且配置没有一劳永逸，大部分情况下还是需要根据自己的项目来进行修改，我也在文件中做了部分解释，具体的自行 google。

这里附带一下 VSCode 中 Json 变量的含义，读者可自行前往查看：[Variables Reference](https://code.visualstudio.com/docs/editor/variables-reference)。


### 2.1 c_cpp_properties.json
    
```javascript
{
    "configurations": [
      {
        "name": "Win64",
        "includePath": ["${workspaceFolder}\\**"],  // 表明前往工作空间下寻找包含文件
        "defines": ["_DEBUG", "UNICODE", "_UNICODE"],
        "windowsSdkVersion": "10.0.18362.0",
        "compilerPath": "E:\\VSCode\\mingw64\\bin\\g++.exe",
        "cStandard": "c17",
        "cppStandard": "c++17",
        "intelliSenseMode": "gcc-x64"
      }
    ],
    "version": 4
}
```

### 2.2. launch.json
    
```javascript
{
    "version": "0.2.0",
    "configurations": [
      {
        "name": "(gdb) Launch", 
        "type": "cppdbg", 
        "request": "launch", 
        // 需要调试的可执行程序，与 tasks 中的可执行程序的名字需保持一致
        "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
        "args": [], 
        "stopAtEntry": false,
        "cwd": "${workspaceRoot}",
        "environment": [],
        // 该选项设置为 false 则使用外部控制台运行程序，程序结束时会立马关闭控制台，需要在末尾加上 system("pause") 
        "externalConsole": false,                               
        "MIMode": "gdb",
        "miDebuggerPath": "E:\\VSCode\\mingw64\\bin\\gdb.exe",
        "preLaunchTask": "C/C++: g++.exe build active file",    // 与 task 中的 label 需要保持一致
        "setupCommands": [
          {
            "description": "Enable pretty-printing for gdb",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
          }
        ]
      }
    ]
  }
```

### 2.3. settings.json

```javascript
{
    "files.associations": {
        "*.py": "python",
        "iostream": "cpp",
        "*.tcc": "cpp",
        "string": "cpp",
        "unordered_map": "cpp",
        "vector": "cpp",
        "ostream": "cpp",
        "new": "cpp",
        "typeinfo": "cpp",
        "deque": "cpp",
        "initializer_list": "cpp",
        "iosfwd": "cpp",
        "fstream": "cpp",
        "sstream": "cpp",
        "map": "c",
        "stdio.h": "c",
        "algorithm": "cpp",
        "atomic": "cpp",
        "bit": "cpp",
        "cctype": "cpp",
        "clocale": "cpp",
        "cmath": "cpp",
        "compare": "cpp",
        "concepts": "cpp",
        "cstddef": "cpp",
        "cstdint": "cpp",
        "cstdio": "cpp",
        "cstdlib": "cpp",
        "cstring": "cpp",
        "ctime": "cpp",
        "cwchar": "cpp",
        "exception": "cpp",
        "ios": "cpp",
        "istream": "cpp",
        "iterator": "cpp",
        "limits": "cpp",
        "memory": "cpp",
        "random": "cpp",
        "set": "cpp",
        "stack": "cpp",
        "stdexcept": "cpp",
        "streambuf": "cpp",
        "system_error": "cpp",
        "tuple": "cpp",
        "type_traits": "cpp",
        "utility": "cpp",
        "xfacet": "cpp",
        "xiosbase": "cpp",
        "xlocale": "cpp",
        "xlocinfo": "cpp",
        "xlocnum": "cpp",
        "xmemory": "cpp",
        "xstddef": "cpp",
        "xstring": "cpp",
        "xtr1common": "cpp",
        "xtree": "cpp",
        "xutility": "cpp",
        "stdlib.h": "c",
        "string.h": "c",
        "iomanip": "cpp",
        "array": "cpp",
        "cstdarg": "cpp",
        "cwctype": "cpp",
        "memory_resource": "cpp",
        "optional": "cpp",
        "string_view": "cpp",
        "unordered_set": "cpp",
        "numeric": "cpp",
        "list": "cpp",
        "bitset": "cpp",
        "chrono": "cpp",
        "forward_list": "cpp",
        "regex": "cpp",
        "valarray": "cpp",
        "cfenv": "cpp",
        "charconv": "cpp",
        "cinttypes": "cpp",
        "codecvt": "cpp",
        "complex": "cpp",
        "condition_variable": "cpp",
        "csetjmp": "cpp",
        "csignal": "cpp",
        "cuchar": "cpp",
        "functional": "cpp",
        "ratio": "cpp",
        "future": "cpp",
        "mutex": "cpp",
        "scoped_allocator": "cpp",
        "shared_mutex": "cpp",
        "thread": "cpp",
        "typeindex": "cpp",
        "queue": "cpp",
        "numbers": "cpp"
    },
    "editor.suggest.snippetsPreventQuickSuggestions": false,
    "aiXcoder.showTrayIcon": true,
    "cmake.outputLogEncoding": "auto",
    "C_Cpp.errorSquiggles": "disabled"
  }
```
    
### 2.4. tasks.json
    
```js
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",                                     //任务执行的是shell命令
            "label": "C/C++: g++.exe build active file",
            "command": "E:\\VSCode\\mingw64\\bin\\g++.exe",         //和launch.josn 中的 preLaunchTask 必须一样
            "args": [
                "-fdiagnostics-color=always",                       // 总是输出颜色代码，即便是在伪终端下
                "-g",
                //"${file}", // 编译当前打开（编辑）的 .cpp 文件
                "${fileDirname}\\*.cpp",                            // 编译当前打开的文件所在目录下的所有 .cpp 文件
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",   // 生成的可执行程序的名字 
            ],
            "options": {
                "cwd": "E:\\VSCode\\mingw64\\bin"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task generated by Debugger."
        }
    ]
}
```
    
## 3 编译并运行一个 `.cpp` 文件

如何安装 VSCode 以及如何安装插件我就不赘述了，这里仅介绍如何创建一个新项目。

新建一个文件夹 TEST，右键用 VSCode 打开。

![image](https://github.com/user-attachments/assets/b9e93fe0-9843-496c-a2ac-de9040404d1d)

在 TEST 文件夹中新建 `.vscode` 文件夹，将前面四个 json 文件放进去（可以自己新建 .json 后缀的文件）。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/b63485a26e77e5297067bc0b19201edd.png#pic_center)

在 VSCode 中，创建 code 文件夹，创建 `func.cpp`，`func.h` 和 `main.cpp` 这三个文件，内容如下：

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/0ebde6e4a1198ff63f9dd1b020589afb.png#pic_center)

要注意，C++ 中自定义的头文件一定要用双引号 `""` 括起来，而不是尖括号 `<>`，否则编译器会前往库文件中寻找头文件，找不到就会报 "func.h: No such file or directory" 的错误。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/a1e5abdcb486ebe80914a09591965225.png#pic_center)

点击上方工具栏中的 *Run->Run Without Debugging*。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/44cb04fefd33d02d6e2bd28355e638e4.png#pic_center)

点击后会出现下面这个，点击红框中所示的选项。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/9f349bc7a926e3b008746db6f3e04b19.png#pic_center)

最后就能成功运行了。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/b74aedf8def63d7d4aef40ab0304e23a.png#pic_center)
