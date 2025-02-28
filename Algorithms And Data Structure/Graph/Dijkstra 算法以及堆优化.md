# 1 朴素 *Dijkstra* 算法

感兴趣的读者可以先阅读同文件夹下的文章：[Prim 算法和 Kruskal 算法.md](./Prim%20算法和%20Kruskal%20算法.md)。*Dijkstra* 算法与 *Prim* 的核心思想是一样的。

*Dijkstra* 算法常用于解决**单源最短路问题**。我们通常将路径的起点称为**源点**，将路径另一端的节点称为**终点**。与此同时，我们可以将**边的权值**称为两个节点之间的**距离**。如果从源点到终点之间至少存在一条**最短路径**，那么我们就将最短路径上**所有边的权值之和**称作**最短距离**。*Dijkstra* 算法适用于**不存在负边权**的**单向图**。

*Dijkstra* 算法采用**贪心策略**，主体由循环构成，最终可以得到**源点到所有节点的最短距离**。从源点开始，每一轮循环由两个步骤组成：**选择**和**更新**——选择与源点**距离最小**的节点（贪心），然后以该节点为中间节点，更新源点到所有**未选择节点**的距离（这一步也被称为松弛操作）。

类似于快速排序每一轮遍历都会筛选出一个元素的最终位置，*Dijkstra* 算法的每一轮循环都会找到源点到一个节点的最短距离。已经选择过的点，不会参于后续的选择过程和更新过程。

在这里，我们假设:
1. 源点为 `s`，图中节点个数为 `n`；
2. `graph` 为邻接矩阵，`graph[u][v]` 表明节点 `u` 和 `v` 的距离，为0表明从到没有边；

我们需要：
1. 定义数组 `dis`，`dis[i]` 表示源点到节点 `i` 的最短距离，初始化为 `INT_MAX` 表明不存在最短路径；
2. 定义数组 `pick`，`pick[i] = false` 表明节点 `i` 还未选取；

更新距离的逻辑是：如果源点到 `u` 的距离 + `u` 到 `v` 的距离 < 源点到 `v` 的距离，则将后者更新为前者。

```cpp
// 函数返回一个数组，表明源点到所有节点的最短距离
vector<int> Dijkstra(const vector<vector<int>>& graph, int s)
{
    int n = graph.size();
    vector<int> dis(n, INT_MAX);
    vector<bool> pick(n, false);
    dis[s] = 0; // 源点到源点的距离为0
    for (int i = 0; i < n; ++i) // 遍历所有节点
    {
        int u = -1, mind = INT_MAX; // u 记录节点，mind 记录最小距离
        for (int j = 0; j < n; ++j) // 选择与源点距离最小的节点
        {
            if (!pick[j] && dis[j] < mind)
            {
                u = j;          // 更新节点
                mind = dis[j];  // 更新最小距离
            }
        }
        if (u == -1) continue;  // u 仍为-1，说明没有找到，进入下一次循环
        pick[u] = true;
        for (int v = 0; v < n; ++v) // 以 u 为中间节点，更新源点到所有未选择节点的距离
        {   
            if (!pick[v] && graph[u][v] != 0 && dis[u] + graph[u][v] < dis[v])
                dis[v] = dis[u] + graph[u][v];
        }
    }

    return dis;
}
```

有读者可能已经发现了，最小生成树包含图中所有的节点，所以我们可以通过 *Prim* 或 *Kruskal* 算法获取最小生成树。但是数组 `d` 维护的是从源点到每个节点的**最短路径的距离**，它并不一定是唯一的，所以通过 *Dijkstra* 算法不能获取最短路径。

*Dijkstra* 算法与 *Prim* 算法还有一个区别在于：当源点不同时，我们**不能保证源点到所有的节点都有路径**。因此在遍历节点的时候，有可能在某一轮循环中没有选取到节点。此时应该进入下一次循环，而不是直接返回。而在 *Prim* 算法中，如果某一轮循环没有选取到更近的节点，说明图本身就不能连通，也就不可能构造最小生成树，所以需要直接返回。

# 2 堆优化的 *Dijkstra* 算法

在朴素 *Dijkstra* 算法中，使用的是邻接矩阵保存所有边的信息。当图是一个稀疏图（节点很多但边很少）时，每选取一个节点时，仍然需要遍历其余的所有节点，算法的效率就会很变得很差。因此可以**将邻接矩阵换成邻接表**。这样在选取节点后，就只需要**遍历从该节点出发的所有边**。

优化的 *Dijkstra* 算法仍然采用贪心策略，每一步都选择与源点**距离最小**的节点。在这之前，我们通过 `dis` 数组去寻找最小距离，而 `dis` 数组需要通过遍历邻接矩阵去更新。现在没有邻接矩阵了，该如何更新 `dis` 的值呢？

我们需要定义一个结构体 `MinDis`，表示**源点到某一节点的最短距离**，并通过一个小顶堆维护所有的最短距离。在每一轮循环中，我们只需要取出树的顶部节点，就可以获得与源点距离最小的节点。然后以该节点为中间节点，更新源点到所有**未选择节点**的距离。

更新逻辑：源点到 `dest` 的最短距离 + 边 `(dest, v)` 的距离 < 源点到 `v` 的最短距离，则将后者更新为前者，同时将这个**新的最短距离**加入到小顶堆维护。

有的读者可能会问，那就是旧的最小距离不是还在小顶堆中吗，会不会影响到选取？答案是不会，因为它“更大”，所以它会沉在小顶堆的底部，不会被选取。

```cpp
struct Edge
{
    int u, v, w;    // u，v 分别为边的起点和终点，w 为边的权值
};
struct MinDis
{   // MinDis 表示一个最短距离，该最短距离的终点是 dest，大小是 mind
    int dest, mind;
    MinDis(int d, int m) : dest(d), mind(m) {};
};
// 函数返回一个数组，表明源点到所有节点的最短距离
int Dijkstra(const vector<list<Edge>>& edges, int start, int end)
{
    int n = edges.size();
    vector<int> dis(n, INT_MAX);
    vector<bool> pick(n, false);
    auto cmp = [](const MinDis& lhs, const MinDis& rhs) { return lhs.mind > rhs.mind; };
    priority_queue<MinDis, vector<MinDis>, decltype(cmp)> pq(cmp);
    dis[s] = 0; // 源点到源点的距离为0
    pq.push(MinDis(s, 0));
    while (!pq.empty())
    {
        MinDis minDist = pq.top();  // 选择与源点距离最小的节点
        pq.pop();
        int u = minDist.dest;
        if (pick[u]) continue;
        pick[u] = true;
        for (const Edge& e : edges[u])  // 遍历从 u 出发的所有边
        {
            if (!pick[e.v] && dis[u] + e.w < dis[e.v])  
            {
                dis[e.v] = dis[u] + e.w;
                pq.push(MinDis(e.v, dis[e.v]));
            }
        }
    }
    
    return dis;
}
```
