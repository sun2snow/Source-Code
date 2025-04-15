#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 1e4 + 10;

int dis[N];
bool vis[N];

int n, m, s;
std::vector<pii> g[N];

void Dijkstra() {
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;
  pq.push({0, s});

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
  std::cin >> n >> m >> s;
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
  }
  Dijkstra();
  for (int i = 1; i <= n; ++i)
    std::cout << (dis[i] == 0x3f3f3f3f ? INT_MAX : dis[i]) << " \n"[i == n];
  return 0;
}
