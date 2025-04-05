#include <bits/stdc++.h>
using lint = long long;
const int N = 1e2 + 10;
// const int N = 5;
const lint INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
lint dis[N][N], cnt[N][N];

void init() {
  std::cin >> n >> m;
  memset(dis, 0x3f, sizeof(dis));
  for (int i = 1; i <= n; ++i) dis[i][i] = 0;
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    dis[u][v] = dis[v][u] = w;
    cnt[u][v] = cnt[v][u] = 1;
  }
}

void Floyd() {
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        if (dis[i][j] > dis[i][k] + dis[k][j]) {
          dis[i][j] = dis[i][k] + dis[k][j];
          cnt[i][j] = cnt[i][k] * cnt[k][j];
        } else if (dis[i][j] == dis[i][k] + dis[k][j])
          cnt[i][j] += cnt[i][k] * cnt[k][j];
      }
}

double calc(int i) {
  double res = 0;
  for (int u = 1; u <= n; ++u) {
    if (u == i) continue;
    for (int v = 1; v <= n; ++v) {
      if (v == i) continue;

      if (dis[u][i] + dis[i][v] == dis[u][v]) res += 1.0 * (cnt[u][i] * cnt[i][v]) / cnt[u][v];
    }
  }

  return res;
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  init();
  Floyd();

  // for (int i = 1; i <= n; ++i)
  //   for (int j = 1; j <= n; ++j) {
  //     std::cout << "(" << i << ", " << j << ") " << dis[i][j] << " " << cnt[i][j] << "\n";
  //   }

  std::cout << std::fixed << std::setprecision(3);
  for (int i = 1; i <= n; ++i)
    std::cout << calc(i) << "\n";
  std::cout.flush();
  return 0;
}
