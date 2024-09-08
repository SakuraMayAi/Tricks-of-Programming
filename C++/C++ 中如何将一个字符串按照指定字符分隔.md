原理是通过 getline() 函数，它会将 stringstream 流对象按照指定的字符进行分隔。如下的打印结果是：

![image](https://github.com/user-attachments/assets/d37d1a7b-0e36-4515-8eef-22ebeb1b1395)

要注意的是，它只会按照指定的字符进行分隔，空格等特殊字符仍然会保留。

```cpp
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    string input = "Hello, world, good, day!";
    stringstream ss(input);
    string slpit;
    vector<string> srtAry;
    while (getline(ss, slpit, ','))    // 按照 ',' 进行分隔，保存在字符串 split 中
        srtAry.push_back(slpit);
    for (auto s : srtAry)
        cout << s << " ";

    return 0;
}
```
