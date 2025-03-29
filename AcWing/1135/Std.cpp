#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 5e4 + 10;

bool vis[N];
int dis[7][N];

std::vector<pii> g[N];
int n, m, ans = 2e9, a[7], mp[N];

void Dijkstra(int id, int *dis) {
  memset(vis, 0, sizeof(vis));
  memset(dis, 0x3f, N << 2);
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  pq.push({0, a[id]});
  dis[a[id]] = 0;
  
  while (!pq.empty()) {
    int u = pq.top().second; pq.pop();
    if (vis[u]) continue;
    vis[u] = true;

    for (auto to : g[u]) {
      if (dis[to.first] > dis[u] + to.second) {
        dis[to.first] = dis[u] + to.second;
        pq.push({dis[to.first], to.first});
      }
    }
  }
}

int main() {
  std::cin >> n >> m;
  a[1] = 1, mp[1] = 1;
  for (int i = 2; i <= 6; ++i) std::cin >> a[i], mp[a[i]] = i;
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
  for (int i = 1; i <= 6; ++i) Dijkstra(i, dis[i]);
  std::sort(a + 2, a + 7);
  do {
    int res = 0;
    for (int i = 2; i <= 6; ++i)
      res += dis[mp[a[i - 1]]][a[i]];
    ans = std::min(ans, res);
  } while (std::next_permutation(a + 2, a + 7));
  std::cout << ans << std::endl;
  return 0;
}
