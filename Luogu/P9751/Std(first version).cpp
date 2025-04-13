#include <bits/stdc++.h>
const int N = 1e4 + 10, K = 110;
using pii = std::pair<int, int>;

struct Node {
  int t; // 到达 u 点的时间
  int u; // 到达的点编号
  int type; // 模 k 分的类

  bool operator<(Node e) const {
    return t > e.t;
  }
};

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
  return st + k * (int)ceil(1.0 * (ed - st) / k);
}

int Dijkstra() {
  std::priority_queue<Node> pq;
  memset(dis, 0x3f, sizeof(dis));
  dis[1][0] = 0;
  pq.push({0, 1, 0});

  while (!pq.empty()) {
    Node now = pq.top(); pq.pop();
    if (vis[now.u][now.type]) continue;
    vis[now.u][now.type] = true;

    for (auto to : g[now.u]) {
      int v = to.first, a = to.second;
      if (now.t >= a) { // 可以直接通过
        if (dis[v][(now.type + 1) % k] > now.t + 1) {
          dis[v][(now.type + 1) % k] = now.t + 1;
          pq.push({dis[v][(now.type + 1) % k], v, (now.type + 1) % k});
        }
      } else { // 可以等待一段时间
        if (dis[v][(now.type + 1) % k] > get(now.t, a) + 1) {
          dis[v][(now.type + 1) % k] = get(now.t, a) + 1;
          pq.push({dis[v][(now.type + 1) % k], v, (now.type + 1) % k});
        }
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
