#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 1e5 + 10;
const int MOD = 100003;

bool vis[N];
int dis[N], cnt[N];

int n, m;
std::vector<int> g[N];

void Dijkstra() {
  memset(dis, 0x3f, sizeof(dis));
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  dis[1] = 0, cnt[1] = 1;
  pq.push({0, 1});

  while (!pq.empty()) {
    int u = pq.top().second; pq.pop(); if (vis[u]) continue; vis[u] = true;
    for (auto v : g[u]) {
      if (dis[v] > dis[u] + 1) {
        dis[v] = dis[u] + 1;
        cnt[v] = cnt[u];
        pq.push({dis[v], v});
      } else if (dis[v] == dis[u] + 1) (cnt[v] += cnt[u]) %= MOD;
    }
  }
}

int main() {
  std::cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  Dijkstra();
  for (int i = 1; i <= n; ++i)
    std::cout << cnt[i] << "\n";
  return 0;
}
