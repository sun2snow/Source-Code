#include <bits/stdc++.h>
const int N = 1e4 + 10, K = 110;
using pii = std::pair<int, int>;

int dis[N][K];
bool vis[N][K];

int n, m, k;
std::vector<pii> g[N];

void input() {
  std::cin >> n >> m >> k;
  for (int i = 1, u, v, w; i <= m; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
  }
}

int get(int st, int ed) { // 让 st+n*k>=ed 的最小整数值 n
  return st < ed ? st + k * (int)ceil(1.0 * (ed - st) / k) : st;
}

int Dijkstra() {
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  memset(dis, 0x3f, sizeof(dis));
  dis[1][0] = 0;
  pq.push({0, 1});

  while (!pq.empty()) {
    int t = pq.top().first, u = pq.top().second; pq.pop();
    if (vis[u][t % k]) continue;
    vis[u][t % k] = true;

    for (auto to : g[u]) {
      int v = to.first, a = to.second;
      if (dis[v][(t + 1) % k] > get(t, a) + 1) {
        dis[v][(t + 1) % k] = get(t, a) + 1;
        pq.push({dis[v][(t + 1) % k], v});
      }
    }
  }

  return dis[n][0] == 0x3f3f3f3f ? -1 : dis[n][0];
}

int main() {
  input();
  std::cout << Dijkstra() << std::endl;
  return 0;
}
