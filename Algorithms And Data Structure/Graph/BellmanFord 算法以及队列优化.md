# 1 朴素 *Bellman-Ford* 算法

*Bellman-Ford* 算法用于解决**单源最短路径问题**。我们通常将路径的起点称为**源点**，将路径另一端的节点称为**终点**。与此同时，我们可以将**边的权值**称为**两个节点之间的距离**。如果从源点到终点之间至少存在一条**最短路径**，那么我们就将最短路径上**所有边的权值之和**称作**最短距离**。*Bellman Ford* 算法适用于**存在负边权**的**单向图**，而且**只能用于单源**，不能用于计算图中任意两点间的最短距离。

由此，算法需要维护一个数组 `d`，来保存源点与所有节点的最短距离。循环结束后，`d[终点]` 即是我们需要的结果。为了求取 `d[终点]`，*Bellman-Ford* 算法对**所有的边**执行**松弛操作**。既然选取的对象是边，就需要声明一个**边结构体**来记录**每条边的信息**，而传递的参数是**邻接表**，邻接表需要根据给定的图或者输入来构造。

初始时，我们需要从源点开始构造路径。算法通过一个循环来**计算源点与计算所有节点**的最短距离。算法总体分为两个步骤：

1. 进行 `n - 1` 次遍历（循环）；
2. 每次遍历对**所有的边**进行松弛操作。

松弛操作：对于边 `(from, to)`，边权为 `val`。`d[from]` 代表源点到节点 `from` 的最短距离，`d[to]` 代表源点到节点 `to` 的最短距离。如果满足 `d[from] + val < d[to]`，则将 `d[to]` 更新为 `d[from] + val`。即如果从源点到 `from` 的最短距离 + 边 `(from, to)` 的距离 < 源点到 `to` 的最短距离，就需要**将后者的值更新为前者**。这一步操作与 *Dijkstra* 算法非常类似。

对所有的边松弛 `n - 1` 次是有实际意义的。松弛 `k` 次，就会更新从源点开始的**边数**为 `k` 的最短路径的最短距离。所以松弛了 `n - 1` 次，一定可以更新从源点到所有节点的最短距离。超过 `n - 1` 次，不管松弛多少次，都不会改变数组 `d` 的值。而如果在第 `n` 次松弛的时候又更新了源点到某个节点的最短距离，就说明图中存在负权环路。

```cpp
struct Edge
{
    int from, to, val;  // from，to 分别为边的起点和终点，val 为边的权值
};

// 计算给定有向图由源点到终点的最短距离
// edges 为边表，保存图中所有的边
// n 为节点数，start 为源点，end 为终点
// 函数返回最短距离，若源点无法到达终点则返回-1
int BellmanFord(const vector<Edge>& edges, int n, int start, int end)
{
    // d[u] 表示源点到节点 u 的最短距离，初始化为 INT_MAX 表明不存在最短路径
    vector<int> d(n, INT_MAX);
    // 令 d[start] = 0 保证在第一次循环更新源点到相邻点的最短距离
    d[start] = 0;
    for (int i = 0; i < n - 1; ++i) // 遍历（循环） n - 1 次
    {
        for (const Edge& e : edges)    // 遍历边表中所有的边
            // 节点 e.to 可以到达，且源点到 `from` 的最短距离 + 边 (from, e.to) 的距离 < 源点到 e.to 的最短距离
            if (d[e.from] != INT_MAX && d[e.from] + e.val < d[e.to])
                d[e.to] = d[e.from] + e.val;    // 更新源点到 e.to 的最短距离
    }

    return d[end] == INT_MAX ? -1 : d[end];
}
```

# 2 检测 *Bellman-Ford* 算法是否存在负权环路

由上一章节可知，如果图中存在负权环路，在松弛完 n - 1 次后再松弛就会使得数组 `d` 发生变化。可借由此判断图中是否存在负权环路。

```cpp
struct Edge
{
    int from, to, val;  // from，to 分别为边的起点和终点，val 为边的权值
};

// 计算给定有向图由源点到终点的最短距离
// edges 为边表，保存图中所有的边
// n 为节点数，start 为源点，end 为终点
// 函数返回最短距离，若源点无法到达终点则返回-1
int BellmanFord(const vector<Edge>& edges, int n, int start, int end)
{
    // d[u] 表示源点到节点 u 的最短距离，初始化为 INT_MAX 表明不存在最短路径
    vector<int> d(n, INT_MAX);
    // 令 d[start] = 0 保证在第一次循环更新源点到相邻点的最短距离
    d[start] = 0;
    for (int i = 0; i < n - 1; ++i) // 遍历（循环） n - 1 次
    {
        for (const Edge& e : edges)    // 遍历边表中所有的边
            // 节点 e.to 可以到达，且源点到 `from` 的最短距离 + 边 `(from, e.to)` 的距离 < 源点到 `e.to` 的最短距离
            if (d[e.from] != INT_MAX && d[e.from] + e.val < d[e.to])
                d[e.to] = d[e.from] + e.val;
    }
    bool flag = false;  // flag = true 表明不存在负权环路
    // 再松弛一次
    for (const Edge& e : edges)    // 遍历边表中所有的边
    {
        // 节点 e.to 可以到达，且源点到 `from` 的最短距离 + 边 `(from, e.to)` 的距离 < 源点到 `e.to` 的最短距离
        if (d[e.from] != INT_MAX && d[e.from] + e.val < d[e.to])
        {
            d[e.to] = d[e.from] + e.val;
            flag = true;
            break;
        }
    }

    return (flag || d[end] == INT_MAX) ? -1 : d[end];
}
```

# 3 队列优化的 *Bellman-Ford* 算法

队列优化的 *Bellman-Ford* 算法，也称 *SPFA(Shortest Path Faster Algorithm)* 算法。

在朴素 *Bellman-Ford* 算法中，每轮循环都会对**所有的边**执行松弛操作。而实际上，在上一轮循环中更新过的节点，才有可能在下一轮循环中被更新，而下一轮循环，又会更新出一批节点。也因此，每一轮循环都会松弛上一轮循环中没有更新过的节点，做了很多无意义的松弛，从而导致算法效率较差。

优化的重点在于**每一轮循环只松弛上一轮循环中更新过的节点**。因此我们需要维护一个队列，来保存每轮循环更新过的节点。那么在每次循环时，我们都会取出队列中的所有节点，然后对以该节点为起点的边执行松弛操作。

同时，由于需要遍历以某节点为起点的所有边，所以采用**邻接表**的方式保存所有的边。而为了保证每个节点在队列中最多存在一个，需要维护一个数组 `pick` 来表明其是否已在队列中。
 
但是队列优化的 *Bellman-Ford* 算法不适用于有负权环路的图，存在负权环路的图，会使得队列始终不为空，导致无限循环。而对于有正权环路图就没关系，因为即使存在环路，在所有的边都充分松弛后，不会再有节点被更新，从而队列为空退出循环。

```cpp
struct Edge
{
    int from, to, val;  // from，to 分别为边的起点和终点，val 为边的权值
};

// 计算给定图由源点到终点的最短距离
// edges 为邻接表，start 为源点，end 为终点
// edges[i] 为链表，保存所有以 i 为起点的边
// 函数返回最短距离，若源点无法到达终点则返回-1
int BellmanFord(const vector<list<Edge>>& edges, int start, int end)
{
    // 节点个数
    int n = edges.size();
    // d[u] 表示源点到节点 u 的最短距离，初始化为 INT_MAX 表明不存在最短路径
    vector<int> d(n, INT_MAX);
    // pick[u] = false 表示节点 u 在队列中
    vector<bool> pick(n, false);
    // 源点入队
    queue<int> qu;
    qu.push(start);
    pick[start] = true;
    // 令 d[start] = 0 保证在第一次循环更新源点到相邻点的最短距离
    d[start] = 0;
    while (!qu.empty())
    {
        int tmp = qu.front();
        qu.pop();
        pick[tmp] = false;  // 标记为不在队列中
        for (const Edge& e : edges[tmp])    //  遍历以 tmp 为起点的所有边
        {
            // 节点 e.to 可以到达，且源点到 `from` 的最短距离 + 边 `(from, e.to)` 的距离 < 源点到 `e.to` 的最短距离
            if (d[tmp] + e.val < d[e.to])
            {
                d[e.to] = d[tmp] + e.val;
                if (!pick[e.to])        // 节点 e.to 不在队列中
                {
                    qu.push(e.to);
                    pick[e.to] = true;  // 标记为在队列中
                }
            }
        }
    }

    return d[end] == INT_MAX ? -1 : d[end];
}
```