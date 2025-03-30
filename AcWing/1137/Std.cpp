#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 1e3 + 10;

bool vis[N];
int dis[N];
int n, m, s, w;
std::vector<pii> g[N];

void Dijkstra() {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  pq.push({dis[0] = 0, 0});
  while (!pq.empty()) {
    int u = pq.top().second; pq.pop(); if (vis[u]) continue; vis[u] = true;
    for (auto to : g[u]) {
      if (dis[to.first] > dis[u] + to.second) {
        dis[to.first] = dis[u] + to.second;
        pq.push({dis[to.first], to.first});
      }
    }
  }
}

int main() {
  while (std::cin >> n >> m >> s) {
    for (int i = 0; i <= n; ++i) g[i].clear();
    for (int i = 0, u, v, w; i < m; ++i) {
      std::cin >> u >> v >> w;
      g[u].push_back({v, w});
    }
    for (std::cin >> w; w; --w) {
      int a;
      std::cin >> a;
      g[0].push_back({a, 0});
    }
    Dijkstra();
    std::cout << (dis[s] == 0x3f3f3f3f ? -1 : dis[s]) << std::endl;
  }
  return 0;
}
