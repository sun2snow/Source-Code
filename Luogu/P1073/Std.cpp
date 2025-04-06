#include <bits/stdc++.h>
#define add(G, u, v) ((G)[u].push_back(v))

const int N = 1e5 + 10;

bool vis[N];
std::vector<int> g[N], gg[N];
int n, m, ans, w[N], f_min[N], f_max[N];

void spfa(int f[], const std::vector<int> *G, int type) {
  memset(vis, 0, sizeof(vis));
  std::queue<int> q;
  if (type == 0) { // 求最小值
    memset(f, 0x3f, N << 2);
    f[1] = w[1];
    q.push(1);
  } else {
    memset(f, -0x3f, N << 2);
    f[n] = w[n];
    q.push(n);
  }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    vis[u] = false;

    for (auto v : G[u]) {
      if (type == 0) {
        if (f[v] > std::min(f[u], w[v])) {
          f[v] = std::min(f[u], w[v]);
          if (!vis[v]) q.push(v), vis[v] = true;
        }
      } else if (type == 1) {
        if (f[v] < std::max(f[u], w[v])) {
          f[v] = std::max(f[u], w[v]);
          if (!vis[v]) q.push(v), vis[v] = true;
        }
      }
    }
  }
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> w[i];
  for (int i = 0, u, v, type; i < m; ++i) {
    std::cin >> u >> v >> type;
    add(g, u, v), add(gg, v, u);
    if (type == 2) add(g, v, u), add(gg, u, v);
  }
  spfa(f_min, g, 0);
  spfa(f_max, gg, 1);

  // for (int i = 1; i <= n; ++i) {
  //   std::cout << f_max[i] << " \n"[i == n];
  // }
  // for (int i = 1; i <= n; ++i) {
  //   std::cout << f_min[i] << " \n"[i == n];
  // }

  for (int i = 1; i <= n; ++i)
    ans = std::max(ans, f_max[i] - f_min[i]);
  std::cout << ans << std::endl;
  return 0;
}
