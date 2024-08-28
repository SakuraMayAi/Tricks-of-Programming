
# 1 全排列
## 1.1 递归(回溯)求全排列的原理
把 $1 \sim n$ 这 $n$ 个整数按照**某个顺序**排列得到的结果称为**这 $n$ 个整数的一个排列**，而**全排列**就是这 $n$ 个整数能形成的**所有排列的集合**。比如 $(1,2,3)，(1,3,2)，(2,1,3)，(2,3,1)，(3,1,2)，(3,2,1)$ 就是整数 $1\sim 3$ 的全排列。那么如何求解 $1 \sim n$ ($n$ 为任意整数)的全排列呢？

下面将以 “求解 $1 \sim n$ ($n$ 为任意整数)的全排列” 这一问题进行解释。

我们可以将这一问题**分解为**若干个子问题：

- “输出以 $1$ 开头的全排列”；
- “输出以 $2$ 开头的全排列”；
- ··· 
- “输出以 $n$ 开头的全排列”。

对于第一个子问题又**可分解为**若干个子问题：

- “输出以 $1,2$ 开头的全排列”；
- “输出以 $1,3$ 开头的全排列”；
- ···
- “输出以 $1,n$ 开头的全排列”。

这一过程，很完美的符合了递归的思想。关于递归和回溯可以参考这篇文章：[递归三部曲和回溯的概念.md](https://github.com/SakuraMayAi/Tricks-of-Programming/blob/main/Data%20Structure/%E9%80%92%E5%BD%92%E4%B8%89%E9%83%A8%E6%9B%B2%E5%92%8C%E5%9B%9E%E6%BA%AF%E7%9A%84%E6%A6%82%E5%BF%B5.md)。

定义 `int` 型数组 `P[maxn + 1]`，每个元素是 $1 \sim n$ 中的一个数字，那么 `P[1] ~ P[n]` 就可以用来保存一个排列。
定义 `bool` 型的数组 `used[maxn + 1]`，其中 `used[x] = true` 表示整数 `x` 已经填入数组 `P`。

假设当前已经填好了 `P[0] ~ P[index - 1]`，接下来需要在 `P[index]` 填入另一个整数（即**递归处理** `P[index]`）。首先需要枚举整数 $1 \sim n$，找出第一个满足 `used[x] = false` 的整数 `x`，然后令 `P[index] = x`，再然后令 `used[x] = true` 表明 `x` 已经被填充。往下就是**递归处理** `P[index + 1]`；当递归完成后，需要在 `P[index]` 填入 `x` 之后的数字，所以需要将 `used[x]` 置为 `false`，以便让 `x` 可以填入其他位置。可以看到，这个过程其实就用到了**回溯**的思想。

### 1.1.1 递归(回溯)求全排列 $1 \sim n$ 的算法代码

```cpp
#include <iostream>
using namespace std;

const int maxn = 10;
int n;
int P[maxn + 1] = { -1 };
bool used[maxn + 1] = { false };

void Backtracking(int index)    // 在 P[index] 填入一个整数
{
    if (index == n + 1)	// 递归边界，此时数组 P 保存了 1 ~ n 的一个排列
    {
        for (int i = 1; i <= n; ++i)
			cout << P[i] << " ";    // 输出当前排列
        cout << endl;
        return;
    }

    for (int x = 1; x <= n; ++x) // 枚举整数 1 ~ n，以便将其填入 P[index]
    {
        if (used[x] == false)		    // 整数 x 还没有被填入过
        {
            P[index] = x;			    // 在第 index 个位置填入 x
            used[x] = true;			    // 表明整数 x 已经被填入了
            Backtracking(index + 1);    // 递归处理 P[index + 1]
            used[x] = false; 		    // 退出递归，还原整数 x 到未填入的状态
        }
    }
}

int main()
{
    cin >> n;
    Backtracking(1);	// 从第一个位置开始填入整数

    return 0;
}
```
### 1.1.2 递归(回溯)求任意序列全排列的 C++ 代码

要求解任意一个序列的全排列的思路和求解 $1 \sim n$ 的思路是一样的，在这里我们使用更加 C++ 的实现方法。假设序列存储在 `vector` 变量 `nums` 中，与此同时我们改用一个 `vector` 变量 `perm` 而非数组 `P` 来存储排列，不再通过传递索引来递归，而是传递 `nums` 的引用。此外，代码中同样需要使用一个 `used` 数组来标记哪些数字已经被填入，大小为 `nums` 数组的大小。

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> perm;
bool used[10] = { false };	// used[i] = false 表明索引为 i 的数已经被选过了

void Backtracking(vector<int>& nums)
{
    if (perm.size() == nums.size())
    {
        for (const auto& i : perm)
            cout << i << " ";
        cout << endl;
        return;
    }
    for (int i = 0; i < nums.size(); ++i)
    {
        if (!used[i])
        {
            used[i] = 1;
            perm.push_back(nums[i]);
            Backtracking(nums);
            perm.pop_back();
            used[i] = 0;
        }
    }
}

int main()
{
    vector<int> nums = { 1, 2, 3 };
    Backtracking(nums);

    return 0;
}
```

## 1.2 递归(回溯)求全排列的应用：n 皇后问题
$n$ 皇后问题：在一个 $n*n$ 的国际象棋棋盘上放置 $n$ 个皇后（棋子），使得这 $n$ 个皇后**两两**不在**同一行、同一列、同一条对角线**上，求合法的方案数。如下左图为合法方案，而右图则为非法方案。
![图片](https://i-blog.csdnimg.cn/blog_migrate/d4e9a4de9d37639f6040648f693a1c00.png#pic_center)

对于这个问题，通过前面回溯求全排列的方法，可以很轻松的解决这个问题。

由于每行只能放置一个皇后，每列也只能放置一个皇后，那么如果把 **$n$ 行**皇后所在的**列号**依次写出，那么就会是 $1 \sim n$ 的一个排列，换句话说，`P[a] = b` 表明第 `a` 行的皇后放在第 `b` 列。按照这个思想，如上左图的五个皇后的排列就可以表示为 `P[5] = (3, 1, 4, 2, 5)`。

因此我们的基本思想是：找出序列 $1 \sim n$ 的所有排列，统计其中符合的方案数即可。

那么如何判断放置方案是否合法呢？对于任意两个皇后来说，假设行号分别为 `i` 和 `j`，那么列号就是 `P[i]` 和 `P[j]`，则：

1. `P[i] != P[j]` 表明她们不在同一行和同一列。
2. **行号差的绝对值**不等于**列号差的绝对值**，即 `abs(i - j) = abs(P[i] - P[j])`，表明不在同一条对角线上。
3. 此时的 `used[x]` 表明第 `x` 列已经放置了一个皇后。

通过这个就可以判断放置方案是否合法。

### 1.2.1 递归(回溯)解决 $n$ 皇后问题的算法代码

```cpp
#include <iostream>
using namespace std;

const int maxn = 10;
int n, cnt = 0; // cnt 保存合法的方案数
int P[maxn + 1] = { -1 };	
bool used[maxn + 1] = { false };

void Backtracking(int index)    // 在 P[index] 填入一个整数
{
    if (index == n + 1)		// 递归边界，此时 P 保存了1 ~ n 的一个排列
    {
		bool flag = true;   // flag = true 表示放置方案是合法的
		for (int i = 1; i <= n; ++i)	// 枚举第一个皇后的行号
		{	
            // 注意 j 一定是从 i + 1开始，因为不能使两个皇后在同一行
			for (int j = i + 1; j <= n; ++j)    // 枚举第二个皇后的行号
				if (abs(i - j) == abs(P[i] - P[j])) flag = false;   // 在一条对角线上，不满足
		}
		if (flag)   // 方案合法
		{
			++cnt;  // 计数+1
			for (int i = 1; i <= n; ++i)// 输出合法方案
				cout << P[i] << " ";			
			cout << endl;
		}
        return;
    }

    for (int x = 1; x <= n; ++x)    // 枚举 1 ~ n 列
    {
        if (used[x] == false)   // 第 x 列还没有放置过皇后
        {
            P[index] = x;       // 在第 index 行第 x 列放置一个皇后
            used[x] = true; 	// 表明第 x 列已经有皇后了
            Backtracking(index + 1);    // 递归处理 P[index + 1]
            used[x] = false; 	// 退出递归，将第 x 列的皇后拿走
        }
    }
}

int main()
{
    cin >> n;
    Backtracking(1);	// 从第一行开始放皇后
	cout << cnt;

    return 0;
}
```

### 1.2.2 优化 $n$ 皇后问题的递归层数和次数

整理好基本框架后，接下来要做的就是进行剪枝操作，也就是减少递归的次数。

在上面的递归过程中我们可以发现：对于有些放置方案，放置好前几个皇后之后，可能剩余的皇后无论怎样放置都不可能合法了，此时就没有必要往下继续递归了。如下右图所示，当放置了前三列的皇后，可以发现剩下的两个皇后无论如何放置都是不合法的，此时就需要退出递归。主要的变化是将判断是否合法的逻辑**提前**，相比于之前的做法，在 $n$ 越大时提升效果越明显。

![图片](https://i-blog.csdnimg.cn/blog_migrate/d4e9a4de9d37639f6040648f693a1c00.png#pic_center)

优化后的算法代码：

```cpp
#include <iostream>
using namespace std;

const int maxn = 10;
int n, cnt = 0; // cnt 保存合法的方案数
int P[maxn + 1] = { -1 };	
bool used[maxn + 1] = { false };

void Backtracking(int index)    // 在 P[index] 填入一个整数（递归处理 P[index]）
{
    if (index == n + 1) // 能到达递归边界的一定是合法方案
    {
		++cnt;  // 计数+1
        for (int i = 1; i <= n; ++i)// 输出合法方案
            cout << P[i] << " ";			
        cout << endl;
    }
    for (int x = 1; x <= n; ++x)    // 枚举 1 ~ n 列
    {
        if (used[x] == false) 	// 当前在处理第 index 行，假设要在第 x 行放置一个皇后
        {
			bool flag = true;   // flag 为 true 表示当前皇后不会和之前的皇后冲突
            for (int pre = 1; pre < index; ++pre)	// 枚举第 index 行上面的皇后
            {	// 第 pre 行皇后的列号为 P[pre]，第 index 行皇后的列号为 x
                if (abs(index - pre) == abs(x - P[pre]))
                {
                    flag = false;	// 和之前的皇后发生冲突，令 flag 为 false
                    break;
                }
            }
			if (flag)	// 当前的放置方案是可行的，继续递归
			{
				P[index] = x;       // 在第 index 行第 x 列放置一个皇后
				used[x] = true; 	// 表明第 x 列已经有皇后了
				Backtracking(index + 1);    // 递归处理 P[index + 1]
				used[x] = false; 	// 退出递归，将第 x 列的皇后拿走
			}
        }
    }
}

int main()
{
    cin >> n;
    Backtracking(1);	// 从第一个位置开始填入整数
	cout << cnt;

    return 0;
}
```

### 1.2.3 递归(回溯)解决 $n$ 皇后问题的 C++ 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 10;
int n, cnt = 0;
vector<int> P = { -1 };  // 用-1填充下标为0的位置
bool used[maxn + 1] = { false };

void Backtracking()
{
    if (P.size() == n + 1)
    {
		++cnt;
        for (int i = 1; i <= n; ++i)
            cout << P[i] << " ";			
        cout << endl;
    }
    for (int x = 1; x <= n; ++x)
    {
        if (!used[x])
        {
			bool flag = true;
            for (int pre = 1; pre < (int)P.size(); ++pre)
            {
                if (abs((int)P.size() - pre) == abs(x - P[pre]))
                {
                    flag = false;
                    break;
                }
            }
			if (flag)
			{
				P.push_back(x);
				used[x] = true;
				Backtracking();
                P.pop_back();
				used[x] = false;
			}
        }
    }
}

int main()
{
    cin >> n;
    Backtracking();	// 从第一个位置开始填入整数
	cout << cnt;

    return 0;
}
```
# 贪心
## 贪心思想求解区间不相交问题
贪心思想是**求解最优化问题**的方法，它总是考虑在当前状态下的**局部最优或较优策略**，从而使全局的结果达到最优。但并非每一个问题都能通过局部最优得到全局最优，因此使用贪心思想求解最优化问题还是需要对其进行严谨的证明。

**区间不相交问题**：给出 $N$ 个**开区间** $(x, y)$，从中选择尽可能多的区间，使得这些区间**两两没有交集**。

首先考虑最简单的情况，如下图所示，如果 $I1$ 被 $I2$ 包含，那么为了满足问题要求显然应该选择更小的 $I1$ ，从而能留出更多的空间来选择其它区间。
![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/5761a22d03c4a411c4b3ef10da7f9047.png#pic_center)

但正常情况下，需要进行选择的区间不止两个。如下图所示，将所有开区间的**左端点**按照**从大到小**的顺序进行排序（数轴上是**右大左小**）。如果**去掉区间包含**的情况，比如 $I1$ 和 $I5$，那么对于剩余所有区间的**右端点**而言，一定有 $y_1>y_2>y_3>y_4$。基于尽可能多的选择区间的前提，以及贪心的思想，我们需要优先考虑与其他区间交集较少的区间。可以观察到对于 $I1$ 来说，它的右侧一部分是没有被其他区间给包含的，也就是虚线右侧的一部分，所以我们首先应该选择 $I1$。然后将所有与 $I1$ 有重合的区间（**右端点**大于 $I1$ **左端点**的区间）给去掉即可。第一个右端点小于等于 $I1$ 左端点的区间，就会成为下一个 “$I1$” 区间。重复上述步骤即可得求解问题。
![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/d57419161707e8c1f46684c55a79742c.png#pic_center)

## 区间不相交问题算法代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 110;

struct Interval {
    int x, y;   // 开区间的左右端点
} I[maxn];

bool cmp(Interval a, Interval b)
{
    if (a.x != b.x) return a.x > b.x;   // 先按左端点从大到小排序
    else return a.y < b.y;              // 左端点相同时，按右端点从小到大排序
}

int main()
{
    int n;  // 初始区间的个数
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> I[i].x >> I[i].y;
    sort(I, I + n, cmp);            // 把区间排序
    int ans = 1, lastX = I[0].x;    // ans 记录不相交区间个数，lastX 保存上一个被选中区间的左端点
    for (int i = 1; i < n; ++i)
    {
        if (I[i].y <= lastX)         // 如果该区间的右端点小于等于 lastX
        {
            lastX = I[i].x;
            ++ans;                  // 不相交区间个数加1
        }
    }
    cout << ans;

    return 0;
}
```
## 贪心算法求解区间选点问题
**区间选点**：给出 N 个**闭区间** $[x, y]$，求最少需要确定多少个点，才能使得每个闭区间中都**至少存在一个点**。例如对于区间 $[1,4]$、$[2,6]$ 和 $[5,7]$ 来说，至少需要两个点，比如$3$和$5$。

区间选点可以用区间不相交同样的方法来解决。如下左图所示，可以明确知道的是 $I1$中的点也一定在 $I2$ 中。和右图一样，去掉区间包含的情况，由于每个闭区间中都需要一个点，因此对于左端点最大的 $I1$ 来说，取点左端点 $x1$ 可以覆盖到更多其他区间。因此区间选点问题只需要将区间不相交问题中的判断条件 I[i].y <= lastX 改为 I[i].y < lastX 即可，为什么呢？

在区间不相交问题中，因为都是开区间，即使两个相邻区间的端点重合它们也没有交集。而在区间选点问题中，由于是闭区间，对于端点就不能用同样的处理方式。如下右图所示，假设 $I1$ 的左端点 $x1$ 和 $I3$ 的右端点 $y3$ 重合了，那么 if(I[i].y <= lastX) 语句为真，于是有 lastX = x3;。在下一个 for 循环中，由于 y4 > x3，if(I[i].y <= lastX) 语句为假，循环结束，但此时没有点存在于 I4 之中，不符合问题要求。因此当相邻区间的端点重合时，存在于左边区间的点就不能用右边区间的左端点来替代，而是将左边区间的左端点作为符合条件的点，这便需要在下一个循环中实现，因此判断的条件要改为小于而不是小于等于。
![在这里插入图片描述](https://i-blog.csdnimg.cn/blog_migrate/4b5d7300549d01c767e552a0d2b79179.png#pic_center)

## 区间选点问题算法代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 110;

struct Interval {
    int x, y;   // 开区间的左右端点
} I[maxn];

bool cmp(Interval a, Interval b)
{
    if (a.x != b.x) return a.x > b.x;   // 先按左端点从大到小排序
    else return a.y < b.y;              // 左端点相同时，按右端点从小到大排序
}

int main()
{
    int n;  // 初始区间的个数
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> I[i].x >> I[i].y;
    sort(I, I + n, cmp);            // 把区间排序
    int ans = 1, lastX = I[0].x;    // ans 记录不相交区间个数，lastX 保存上一个被选中区间的左端点
    for (int i = 1; i < n; ++i)
    {
        if (I[i].y < lastX)         // 如果该区间的右端点小于 lastX
        {
            lastX = I[i].x;
            ++ans;                  // 不相交区间个数加1
        }
    }
    cout << ans;

    return 0;
}
```
---
**希望本篇博客能对你有所帮助，也希望看官能动动小手点个赞哟~~。**
