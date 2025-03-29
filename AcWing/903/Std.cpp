#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 110;

bool vis[N];
int dis[N];

std::vector<pii> g[N];
int m, n, ans = 2e9, level[N];

void init() { // 读入+建图
  std::cin >> m >> n;
  for (int i = 1, p, l, x; i <= n; ++i) {
    std::cin >> p >> l >> x;
    g[0].push_back({i, p});
    level[i] = l;
    for (int t, v; x; --x) {
      std::cin >> t >> v;
      g[t].push_back({i, v});
    }
  }
}

void Dijkstra(int i) {
  memset(vis, 0, sizeof(vis));
  memset(dis, 0x3f, sizeof(dis));

  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  pq.push({0, 0});
  dis[0] = 0;
  
  while (!pq.empty()) {
    int u = pq.top().second; pq.pop();
    if (vis[u]) continue;
    vis[u] = true;

    for (auto to : g[u]) {
      if (level[to.first] < i || level[to.first] > i + m) continue; // 越级
      if (dis[to.first] > dis[u] + to.second) {
        dis[to.first] = dis[u] + to.second;
        pq.push({dis[to.first], to.first});
      }
    }
  }

  ans = std::min(ans, dis[1]);
}

void process() { // 跑最短路
  for (int i = level[1] - m; i <= level[1]; ++i) // 枚举等级范围为 [i,i+m]
    Dijkstra(i);
}

void output() {
  std::cout << ans << std::endl;
}

int main() {
  init();

  // for (int i = 1; i <= n; ++i)
  //   std::cout << level[i] << " \n"[i == n];

  process();
  output();
  return 0;
}
