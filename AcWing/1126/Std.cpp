#include <bits/stdc++.h>
const int N = 2e3 + 10;

bool vis[N];
int n, m, s, t;
double dis[N], w[N][N];

void Dijkstra() {
  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 1;
  for (int i = 1; i < n; ++i) {
    int t = -1;
    for (int j = 1; j <= n; ++j)
      if (!vis[j] && (t == -1 || dis[j] > dis[t])) t = j;
    
    vis[t] = true;
    for (int j = 1; j <= n; ++j)
      dis[j] = std::max(dis[j], dis[t] * w[j][t]);
  }
}

int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int x, y, z;
    std::cin >> x >> y >> z;
    w[x][y] = w[y][x] = std::max(w[x][y], (double)(1 - z / 100.0));
  }

  std::cin >> s >> t;

  // for (int i = 1; i <= n; ++i, puts(""))
  //   for (int j = 1; j <= m; ++j)
  //     printf("%.3f  ", w[i][j]);

  Dijkstra();
  printf("%.8f\n", 100 / dis[t]);
  return 0;
}
