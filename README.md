# Source-Code
残阳如血 OI 记录合集

## Introduce

- `AcWing`：[AcWing](https://www.acwing.com/) 中题目练习。
- `Luogu`：[洛谷](https://www.luogu.com.cn/) 中题目练习。
- `Contest`：记录在参加模拟赛的代码。

## Tricks
- 树上统计距离可以转化为每条边的贡献。


## Warning
- `abs()` 与 `std::abs()` 不相同。一定要使用 `std::abs()`；
- 双端队列 BFS 必须用 **三角不等式** 检查，标记 `vis` 数组的方式要求和 $\text{Dijkstra}$ 相同。
- Floyd 更新加入 $k$ 号点的情况时，也必须遍历 $u,v\in[1,n]$。
- 线段树一定要开 $4$ 倍数组！线段树一定要开 $4$ 倍数组！线段树一定要开 $4$ 倍数组！
