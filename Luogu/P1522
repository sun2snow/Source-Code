#include <bits/stdc++.h>
const int N = 200;
const double eps = 1e-8;

double ans = 2e9, g[N][N];
int n, x[N], y[N];
double max_d[N]; // 到达每个点的最远距离
double d[N]; // 直径

// 并查集
int fa[N];
int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
  if (find(x) != find(y)) fa[find(x)] = find(y);
}

double dist(int x1, int y1, int x2, int y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void Floyd() {
  for (int k = 1; k <= n; ++k) for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
    g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
}

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1; i <= n; ++i) std::cin >> x[i] >> y[i];
  for (int i = 1; i <= n; ++i) {
    for (int j = 1, w; j <= n; ++j) {
      scanf("%1d", &w);
      if (i == j) g[i][j] = 0;
      else if (w == 1) g[i][j] = dist(x[i], y[i], x[j], y[j]);
      else g[i][j] = 1e9;
    }
  }
  Floyd();
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (fabs(g[i][j] - 1e9) < eps) continue;
      merge(i, j);
      max_d[i] = std::max(max_d[i], g[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i)
    d[find(i)] = std::max(d[find(i)], max_d[i]);
  
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (fabs(g[i][j] - 1e9) < eps) {
        ans = std::min(ans, std::max({d[find(i)], d[find(j)], max_d[i] + max_d[j] + dist(x[i], y[i], x[j], y[j])}));
      }
    }
  }
  
  std::cout << std::fixed << std::setprecision(6) << ans << std::endl;
  return 0;
}
