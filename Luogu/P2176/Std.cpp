#include <bits/stdc++.h>
const int N = 1e2 + 10, M = 5e3 + 10;

struct Edge {
  int u, v, w;
} e[M];

int dis[N];
bool vis[N];

int n, m, len, ans, g[N][N];

int Dijkstra() {
  memset(vis, 0, sizeof(vis));
  memset(dis, 0x3f, sizeof(dis));
  dis[1] = 0;
  for (int i = 1; i < n; ++i) {
    int t = -1;
    for (int j = 1; j <= n; ++j)
      if (!vis[j] && (t == -1 || dis[j] < dis[t])) t = j;
    
    vis[t] = true;
    for (int j = 1; j <= n; ++j)
      dis[j] = std::min(dis[j], dis[t] + g[t][j]);
  }

  return dis[n];
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m;
  memset(g, 0x3f, sizeof(g));
  for (int i = 1; i <= m; ++i) {
    std::cin >> e[i].u >> e[i].v >> e[i].w;
    g[e[i].u][e[i].v] = g[e[i].v][e[i].u] = e[i].w;
  }

  len = Dijkstra();

  // std::cout << len << std::endl;

  for (int i = 1; i <= m; ++i) {
    g[e[i].u][e[i].v] = g[e[i].v][e[i].u] = 2 * e[i].w;

    ans = std::max(ans, Dijkstra() - len);

    g[e[i].u][e[i].v] = g[e[i].v][e[i].u] = e[i].w;
  }

  std::cout << ans << std::endl;
  return 0;
}
