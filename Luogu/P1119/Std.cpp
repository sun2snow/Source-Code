#include <bits/stdc++.h>
const int N = 2e2 + 10;

int n, m, T, p = 1, q, t[N], dis[N][N]; // p 维护当前第几个村庄重建好了

void Floyd(int k) {
  dis[k][k] = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m;
  memset(dis, 0x3f, sizeof(dis));
  for (int i = 1; i <= n; ++i) std::cin >> t[i];
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w, ++u, ++v;
    dis[u][v] = dis[v][u] = std::min(dis[u][v], w);
  }
  std::cin >> q;

  while (p <= n && t[p] == 0) Floyd(p++);

  for (int u, v, tim; q; --q) {
    std::cin >> u >> v >> tim, ++u, ++v;
    while (T != tim) {
      ++T;
      while (p <= n && t[p] == T) Floyd(p++);
    }
    
    if (t[u] > tim || t[v] > tim) std::cout << "-1\n";
    else std::cout << (dis[u][v] == 0x3f3f3f3f ? -1 : dis[u][v]) << "\n";
  }
  std::cout.flush();
  return 0;
}
