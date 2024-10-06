# 1 C++ 编译环境安装

## 1.1 必备插件

红框中的四个插件是必备的，安装后可通过上方的 *Run* 运行或调试代码。其中 Code Runner 插件是我比较推荐的**单文件**快速运行插件，安装后可以通过按下 `Crtl + Alt + N` 快捷键（可以更改）快速编译运行单个 `.c` 或 `.cpp` 文件。

![image](https://github.com/user-attachments/assets/2af119cc-8554-45b8-8104-6b995d345799)

不用 Code Runner 也可以使用 C/C++ Complier 插件。

![image](https://github.com/user-attachments/assets/cf824a12-df95-4040-b465-16f207e1436c)

# 1.2 .json 文件配置
这里的 json 文件只是作为我个人的配置，仅供参考使用，并不能适用所有工程。而且配置没有一劳永逸，大部分情况下还是需要根据自己的项目来进行修改，我也在文件中做了部分解释，具体的自行 google。

这里附带一下 VSCode 中 Json 变量的含义，读者可自行前往查看：[Variables Reference](https://code.visualstudio.com/docs/editor/variables-reference)。

**注意！所有的路径请参照自己的 mingw 安装的路径进行修改！**
## 1. c_cpp_properties.json

```js
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
## 2. launch.json

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
## 3. settings.json

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
## 4. tasks.json

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
# 1.3 编译并运行一个 `.cpp` 文件
如何安装 VSCode 以及如何安装插件我就不赘述了，读者可以自己搜索一下，这里仅介绍如何创建一个新项目。

新建一个文件夹 `TEST`，右键用 VSCode 打开。

![image](https://github.com/user-attachments/assets/b9e93fe0-9843-496c-a2ac-de9040404d1d)

在 TEST 文件夹中新建 `.VSCode` 文件夹，将四个 json 文件放进去（可以自己新建 .json 后缀的文件）.。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/b63485a26e77e5297067bc0b19201edd.png#pic_center)

在 VSCode 中，创建 `code` 文件夹，创建 `func.cpp`，`func.h` 和 `main.cpp` 这三个文件，内容如下：

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/0ebde6e4a1198ff63f9dd1b020589afb.png#pic_center)

要注意，C++ 中自定义的头文件一定要用双引号 `""` 括起来，而不是尖括号 `<>`，否则编译器会前往库文件中寻找头文件，找不到就会报 "func.h: No such file or directory" 的错误。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/a1e5abdcb486ebe80914a09591965225.png#pic_center)

点击上方工具栏中的 *Run->Run Without Debugging*。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/44cb04fefd33d02d6e2bd28355e638e4.png#pic_center)

点击后会出现下面这个，点击红框中所示的选项。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/9f349bc7a926e3b008746db6f3e04b19.png#pic_center)

最后就能成功运行了。

![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/b74aedf8def63d7d4aef40ab0304e23a.png#pic_center)

# 2 插件推荐

# 3 VS Code 相关设置

## 3.1自动补全括号

在设置中搜索 `autoClosingBrackets`，然后将 `Editor: Auto Closing Brackets` 选项设置为 `always` 或者 `languageDefined`。该选项控制是否总在添加左括号后补充右括号。

其次勾选 `C_Cpp: Autocomplete Add Parentheses`，该选项针对 C++。如果 `Editor: Auto Closing Brackets` 的值为 `true`，那么在 C++ 中自动补全（尤其是函数）后会自动添加上左右括号。

![image](https://github.com/user-attachments/assets/634265cd-cd8a-4760-8454-9e018766887f)

### 自动补全尖括号

默认情况下，在你输入左尖括号 `<` 后，并不会补全右尖括号。比如当你想使用 `vector`、`map` 这些模版的时候，你还是希望能自动补上的来快速填入类型的。但是 C++ 的语言配置选项中没有这一项，需要手动修改。

在你的 VSCode 安装目录下，找到并打开 *"Microsoft VS Code\resources\app\extensions\cpp"* 文件夹，如图所示。

![image](https://github.com/user-attachments/assets/5cc1230e-be5e-4fde-ba0e-d9adce661e6a)

打开 `language-configuration.json` 文件，把里面的 Json 代码复制到 [在线 Json 格式校验](https://www.bejson.com/) 后，就能看到格式化的 Json 代码了（当然这里只是安利一下这个格式化网站，实际上你还是需要在 `language-configuration.json` 文件 中进行修改）。

![image](https://github.com/user-attachments/assets/3e7c25ce-6296-4998-a46c-ba25b4dbdda0)

其中键 `autoClosingPairs` 后面方括号对儿 `[...]` 里面就指定了可以补全的符号，随便找一个位置添加 `{"open":"<","close":">"}` 就好了，如果放在中间的话别忘记末尾加上英文逗号 `,` 哦。实际上我不是很推荐补全尖括号，因为尖括号用于模版类型出现的概率，要小于输入小于号、左移运算符等情况，这种情况下还自动补全就很头疼了。
