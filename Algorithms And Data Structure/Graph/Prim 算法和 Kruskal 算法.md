# 前言

*Prim* 算法和 *Kruskal* 算法都是用来计算**最小生成树的权值和**，或者**获取最小生成树**的算法。它们会以最小的权值或代价将图中所有的节点连接到一起，构成一个**最小连通子图**。

# *Prim* 算法

在 *Prim* 算法中，我们将**边的权值**视作**两个节点之间的距离**。

*Prim* 算法采用贪心策略，每次都选取距离最小生成树**最近的节点**，并将其加入到最小生成树中。算法通过一个循环来实现这一过程，每一轮循环可以分为三个步骤：
1. 寻找距离最小生成树最近的节点 `u`；
2. 将节点 `u` 加入最小生成树，并更新最小生成树权值和；
3. 以节点 `u` 为基点，更新最小生成树与剩余节点的距离。

要注意，此处的算法默认节点编号从0开始，如果你的场景中是从1开始，需要对循环条件做相应的修改。同时，也需要更改 `d[0] = 0` 为 `d[0] = 1`。

```cpp
// 计算给定图的最小生成树的权值之和
// graph 为邻接矩阵，graph[u][v] = 0 表明从 u 到 v 没有边
// n 为顶点个数。函数返回最小生成树的权值和
int Prim(const vector<vector<int>>& graph, int n)
{
    // d[u] 表示节点 u 到最小生成树的最小距离
    // 初始化为 INT_MAX 表明其不在最小生成树中
    vector<int> d(n, INT_MAX);
    // pick 标记节点是否已经选择过
    vector<bool> pick(n, false);
    // 令 d[0] = 0保证在第一次循环时必定选中节点0
    d[0] = 0;
    int sum = 0;    // 权值和
    for (int i = 0; i < n; ++i) // 遍历所有节点
    {
        // 寻找距离最小生成数最近的节点 u
        int u = -1, mind = INT_MAX; // u 记录最近节点，mind 保存最小距离
        for (int j = 0; j < n; ++j)
        {
            if (!pick[j] && d[j] < mind)    // 节点 j 没选过且距离最小生成树更近
            {
                u = j;          // 更新节点值
                mind = d[j];    // 更新最小距离
            }
        }

        // 将节点 u 加入最小生成树，并更新最小生成树权值和
        if (u == -1) return -1; // 找不到符合要求的 u，退出循环
        pick[u] = true;
        sum += d[u];

        // 以节点 u 为基点，更新最小生成树与剩余节点的距离
        for (int v = 0; v < n; ++v)
        {   // 如果 v 没有选择过，且 u 和 v 的距离相较于之前更近
            if (!pick[v] && graph[u][v] != 0 && graph[u][v] < d[v])
                d[v] = graph[u][v];
        }
    }

    return sum;
}
```

# *Kruskal* 算法

*Kruskal* 算法同样采用贪心策略，但它是每次都选取**权值最小的边**。每次选取边时，为了**避免连通子图产生环**，需要确保这条边的两个端点至少有一个不在连通子图中。显然，最快速的判断方法就是利用**并查集**。

首先将所有的边按照权值**由小到大**进行排序，通过一个循环来将所有的边加入到连通子图中，每一轮循环大致可以分为两个步骤：

1. 从排好序的边表中选取一个边，获取其两个端点的根节点；
2. 如果根节点不同，说明不会生成环，将边加入到最小生成树中。

```cpp
struct Edge
{
    int u, v, val;  // 端点，权值
};
vector<int> root;   // root[x] 表示节点 x 的根节点
// 寻找节点 x 的根节点，同时执行路径压缩
int Find(int x) { return root[x] == x ? x : root[x] = Find(root[x]); }
// 按边的权值由小到大进行排序
bool cmp(Edge a, Edge b) { return a.val < b.val; }

// 计算给定图的最小生成树的权值之和
// edge 保存所有边的信息，n 为顶点数，m 为边数
int Kruskal(vector<Edge>& edge, int n, int m)
{
    root.resize(n, 0);
    // sum 为权值和，num 为连通子图的边数
    int sum = 0, num = 0;
    for (int i = 0; i < n; ++i) root[i] = i;
    sort(edge.begin(), edge.begin() + m, cmp);
    for (int i = 0; i < m; ++i)
    {
        int ru = Find(edge[i].u);   // 获取 u 的根节点
        int rv = Find(edge[i].v);   // 获取 v 的根节点
        if (ru != rv)   // 根节点不同，说明 u 和 v 不同时在最小生成树中
        {
            root[ru] = rv;          // 都加入到连通子图中
            sum += edge[i].val;     // 更新权值和
            if (++num == n - 1) break; // 边数等于顶点数减1，结束算法
        }
    }
    if (num != n - 1) return 0; // 图无法连通，返回-1

    return sum;
}
```