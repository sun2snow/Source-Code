#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 1e3 + 10;

int dis[N];
bool vis[N];

int n, m, k;
std::vector<pii> g[N];

void init() {
  std::cin >> n >> m >> k;
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
}

bool check(int x) { // 返回 1->N 的路径中是否有一条路径长度>x的边的边数<=k
  memset(vis, 0, sizeof(vis));
  memset(dis, 0x3f, sizeof(dis));
  std::deque<int> q;
  q.push_back(1);
  dis[1] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop_front();

    if (vis[u]) continue;
    vis[u] = true;

    for (auto to : g[u]) {
      int w = to.second > x;

      if (dis[to.first] > dis[u] + w) {
        dis[to.first] = dis[u] + w;
        if (w) q.push_back(to.first);
        else q.push_front(to.first);
      }
    }
  }

  return dis[n] <= k;
}

void process() {
  int l = -1, r = 1e6 + 10;
  while (l + 1 != r) {
    int mid = l + r >> 1;
    if (check(mid)) r = mid;
    else l = mid;
  }

  std::cout << (r == 1e6 + 10 ? -1 : r) << std::endl;
}

int main() {
  init();
  process();
  return 0;
}
