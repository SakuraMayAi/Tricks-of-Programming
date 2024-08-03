# 默认排序
对于 `map` 和 `set` 等关联容器，默认都是按照**键**由小到大进行排序。如下代码。

```cpp
#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<string, int> mp;
	mp["a"] = 4;
	mp["b"] = 3;
	mp["c"] = 2;
	mp["d"] = 1;

    for (auto it = mp.cbegin(); it != mp.cend(); ++it)
		cout << it->first << " " << it->second << endl;

    return 0;
}
```

打印结果如下。
```cpp
a 4
b 3
c 2
d 1
```

# 对键（单一类型）按照自定义规则排序

关联容器的自定义规则，和顺序容器定义一个单独的 `cmp()` 函数不一样。关联容器的自定义规则需要放在一个**结构体**或者**类**中，然后对函数运算符 `()` 进行重载。而且**自定义规则**是添加在容器定义时，而不是通过 `sort()` 函数对容器进行排序。

> 当比较规则放在类中时，切记要声明为 `public` 属性。

这里还有一点要注意，C++17 之后的标准规定了，对于自定义规则中的重载函数运算符函数，必须定义为**常量成员函数**，也就是在参数列表之后加上 `const` 关键字。

```cpp
#include <iostream>
#include <map>
using namespace std;

struct rule
{
	bool operator()(string a, string b) const	// 必须加上 const 关键字
    {
		return a > b;   // 按照字符串由大到小排序
	}
};

int main()
{
    map<string, int, rule> mp;
	mp["a"] = 4;
	mp["b"] = 3;
	mp["c"] = 2;
	mp["d"] = 1;

    for (auto it = mp.cbegin(); it != mp.cend(); ++it)
		cout << it->first << " " << it->second << endl;

    return 0;
}
```

打印结果如下。
```cpp
d 1
c 2
b 3
a 4
```

# 对键按照自定义规则排序（键为复合类型）

当关联容器的键是复合类型是（结构体或者类）时，自定义的规则和单一类型时没什么区别，代码如下。

```cpp
#include <iostream>
#include <map>
using namespace std;

typedef struct
{
    string s;
    int n;
} node;

struct rule
{   // s 不等时按照 s 由大到小排序，否则按照 n 由大到小进行排序
	bool operator()(node a, node b) const	// 必须加上 const 关键字
    {
		if (a.s != b.s) return a.s > b.s;
        else return a.n > b.n;
	}
};

int main()
{
    node tmp;
    map<node, int, rule> mp;
    tmp.s = "a";
    tmp.n = 1;
    mp[tmp] = 1;

    tmp.s = "a";
    tmp.n = 2;
    mp[tmp] = 1;

    tmp.s = "b";
    tmp.n = 1;
    mp[tmp] = 1;

    tmp.s = "b";
    tmp.n = 2;
    mp[tmp] = 1;

    for (auto it = mp.cbegin(); it != mp.cend(); ++it)
		cout << it->first.s << " " << it->first.n << endl;

    return 0;
}
```

打印结果如下。
```cpp
b 2
b 1
a 2
a 1
```

# 对值按照自定义规则排序

关联容器并不能直接对**值**按照自定义规则排序，需要通过顺序容器来实现。比如下面代码，通过关联容器的迭代器，构造一个 `vector` 对象 `vec`。要注意 `vec` 中的元素类型要和关联容器保持一致。然后对 `vec` 进行排序，就能得到按照值由大到小的键值对。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

bool cmp(const pair<string, int>& a, const pair<string, int>& b)
{
    return a.second > b.second;   // 按照整数由大到小排序
}

int main()
{
    map<string, int> mp;
	mp["a"] = 4;
	mp["b"] = 3;
	mp["c"] = 2;
	mp["d"] = 1;

    vector<pair<string, int>> vec(mp.cbegin(), mp.cend());	// 通过关联容器的迭代器构造vector 对象，注意元素类型一致
    sort(vec.begin(), vec.end(), cmp);

    for (auto it = vec.cbegin(); it != vec.cend(); ++it)
		cout << it->first << " " << it->second << endl;

    return 0;
}
```

打印结果如下。
```cpp
a 4
b 3
c 2
d 1
```
