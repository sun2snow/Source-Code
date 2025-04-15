#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 5e4 + 10;

int dis[N];
bool vis[N];

int n, m, Q;
std::vector<pii> g[N];

void Dijkstra() {
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  memset(dis, 0x3f, sizeof(dis));
  dis[1] = 0;
  pq.push({0, 1});

  while (!pq.empty()) {
    int u = pq.top().second; pq.pop();
    if (vis[u]) continue; vis[u] = true;
    for (auto to : g[u]) {
      if (dis[to.first] > dis[u] + to.second) {
        dis[to.first] = dis[u] + to.second;
        pq.push({dis[to.first], to.first});
      }
    }
  }
}

int main() {
  std::cin >> n >> m >> Q;
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
  Dijkstra();
  for (int u, v; Q; --Q) {
    std::cin >> u >> v;
    std::cout << dis[u] + dis[v] << "\n";
  }
  return 0;
}
