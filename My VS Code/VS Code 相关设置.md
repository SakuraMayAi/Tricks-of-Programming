# 单词分隔

在中英文混合时，有时候我想双击选中单词，VSCode 并不会识别中文以及中文的符号，导致它们也一并被选入了，如图所示：

![image](https://github.com/user-attachments/assets/e5f554d6-5942-48ce-947d-de821fd43c0b)

在 VSCode 的设置中，搜索 *Word Separators*，在 *Editor: Word Separator* 一栏中，就是选中单词时会自动识别的分隔符号，填入一些常见的中文符号，就能分隔中英文了：

![image](https://github.com/user-attachments/assets/922aa9c3-88a4-46b3-8acc-bf3da82d9451)

要注意，汉字和字母挨着的时候是无法分隔的。因为我个人比较喜欢在英文单词的前后加空格，所以当我双击选中英文单词时，空格就能帮我分隔掉中文。如果你跟我的习惯不一样，那么设置中文符号间隔就不太够用了。

# 自动补全括号

在设置中搜索 *autoClosingBrackets*，然后将 *Editor: Auto Closing Brackets* 选项设置为 *always* 或者 *languageDefined*。该选项控制是否总在添加左括号后补充右括号。

其次勾选 *C_Cpp: Autocomplete Add Parentheses*，该选项针对 C++。如果 *Editor: Auto Closing Brackets* 的值为 *true*，那么在 C++ 中自动补全（尤其是函数）后会自动添加上左右括号。

## 自动补全尖括号

默认情况下，在你输入左尖括号 `<` 后，并不会补全右尖括号。比如当你想使用 `vector`、`map` 这些模版的时候，你还是希望能自动补上的来快速填入类型的。但是 C++ 的语言配置选项中没有这一项，需要手动修改。

在你的 VSCode 安装目录下，找到并打开 *"Microsoft VS Code\resources\app\extensions\cpp"* 文件夹，如图所示。

![image](https://github.com/user-attachments/assets/5cc1230e-be5e-4fde-ba0e-d9adce661e6a)

打开 `language-configuration.json` 文件，把里面的 Json 代码复制到 [在线 Json 格式校验](https://www.bejson.com/) 后，就能看到格式化的 Json 代码了（当然这里只是安利一下这个格式化网站，实际上你还是需要在 `language-configuration.json` 文件 中进行修改）。

![image](https://github.com/user-attachments/assets/3e7c25ce-6296-4998-a46c-ba25b4dbdda0)

其中键 `autoClosingPairs` 后面方括号对儿 `[...]` 里面就指定了可以补全的符号，随便找一个位置添加 `{"open":"<","close":">"}` 就好了，如果放在中间的话别忘记末尾加上英文逗号 `,` 哦。实际上我不是很推荐补全尖括号，因为尖括号用于模版类型出现的概率，要小于输入小于号、左移运算符等情况，这种情况下还自动补全就很头疼了。
