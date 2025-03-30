#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 25e3 + 10;


std::vector<pii> g[N];
int n, ma, mb, s, dis[N];
bool vis[N]; // 标记每个点是否被访问过

int ind[N];
std::queue<int> q;

int cnt_block, id[N]; // 每个点所属连通块的编号
std::vector<int> block[N]; // 每个连通块包含的点

void dfs(int u, int bid) {
  id[u] = bid;
  block[bid].push_back(u);
  for (auto to : g[u])
    if (!id[to.first]) dfs(to.first, bid);
}

void Dijkstra(int bid) {
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  for (auto u : block[bid]) pq.push({dis[u], u});

  while (!pq.empty()) {
    int u = pq.top().second; pq.pop();
    if (vis[u]) continue;
    vis[u] = true;

    for (auto to : g[u]) {
      int v = to.first, w = to.second;

      if (id[v] != bid && !--ind[id[v]]) q.push(id[v]);
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (id[v] == bid) pq.push({dis[v], v});
      }
    }
  }
}

int main() {
  std::cin >> n >> ma >> mb >> s;
  for (int i = 0, u, v, w; i < ma; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  for (int i = 1; i <= n; ++i)
    if (!id[i]) dfs(i, ++cnt_block);

  for (int i = 0, u, v, w; i < mb; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    ++ind[id[v]];
  }

  for (int i = 1; i <= cnt_block; ++i)
    if (!ind[i]) q.push(i);
  
  // std::cout << "q.size()=" << q.size() << std::endl;

  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop(); // u 为连通块编号
    Dijkstra(u);
  }

  // for (int i = 1; i <= n; ++i)
  //   std::cout << dis[i] << " \n"[i == n];

  for  (int i = 1; i <= n; ++i) {
    if (dis[i] > 0x3f3f3f3f / 2) std::cout << "NO PATH\n";
    else std::cout << dis[i] << "\n";
  }
  return 0;
}
