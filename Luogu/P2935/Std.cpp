#include <bits/stdc++.h>
const int N = 5e2 + 10;

int n, t, m, ans, sum_min = 2e9, a[N], g[N][N];

int main() {
  std::cin >> n >> t >> m;
  for (int i = 0; i < t; ++i) std::cin >> a[i];
  memset(g, 0x3f, sizeof(g));
  for (int i = 1; i <= n; ++i) g[i][i] = 0;
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g[u][v] = g[v][u] = std::min(g[u][v], w);
  }
  
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);

  for (int i = 1; i <= n; ++i) {
    int sum = 0;
    for (int j = 0; j < t; ++j) sum += g[i][a[j]];
    if (sum < sum_min) ans = i, sum_min = sum;
  }
  std::cout << ans << std::endl;
  return 0;
}
