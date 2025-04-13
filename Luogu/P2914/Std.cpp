#include <bits/stdc++.h>
using lint = long long;
const int N = 1e3 + 10;

bool vis[N];
double dis[N];

int n, m, x[N], y[N];
double k, ans, g[N][N];

double dist(lint x1, lint y1, lint x2, lint y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void Dijkstra() {
  for (int i = 2; i <= n; ++i) dis[i] = 1e9;
  for (int i = 1; i < n; ++i) {
    int t = -1;
    for (int j = 1; j <= n; ++j)
      if (!vis[j] && (t == -1 || dis[j] < dis[t])) t = j;
    vis[t] = true;
    for (int j = 1; j <= n; ++j) {
      if (dis[j] > dis[t] + g[t][j]) {
        dis[j] = dis[t] + g[t][j];
      }
    }
  }
}

int main() {
  std::cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) std::cin >> x[i] >> y[i];
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      if (i == j) g[i][j] = 0;
      else if (dist(x[i], y[i], x[j], y[j]) <= k) g[i][j] = dist(x[i], y[i], x[j], y[j]);
      else g[i][j] = 1e9;
    }
  for (int i = 0, u, v; i < m; ++i)
    std::cin >> u >> v, g[u][v] = g[v][u] = 0;
  Dijkstra();
  if (fabs(dis[n] - 1e9) < 1e-6) std::cout << "-1\n";
  else std::cout << (int)(dis[n] * 1000) << std::endl;
  return 0;
}
