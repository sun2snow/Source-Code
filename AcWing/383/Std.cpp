#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 1e3 + 10;

struct Data {
  int t;
  int u;
  int type;

  bool operator<(const Data &e) const {
    return t > e.t;
  }
};

bool vis[N][2];
int dis[N][2], cnt[N][2];

int T, n, m, s, t;
std::vector<pii> g[N];

void input() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) g[i].clear();
  for (int i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g[u].push_back({v, w});
  }
  std::cin >> s >> t;
}

int Dijkstra() {
  std::priority_queue<Data> pq;
  memset(dis, 0x3f, sizeof(dis));
  memset(cnt, 0, sizeof(cnt));
  memset(vis, 0, sizeof(vis));
  pq.push({0, s, 0});
  dis[s][0] = 0, cnt[s][0] = 1;

  while (!pq.empty()) {
    auto cur = pq.top(); pq.pop();
    if (vis[cur.u][cur.type]) continue;
    vis[cur.u][cur.type] = true;

    for (auto to : g[cur.u]) {
      int v = to.first, w = to.second;
      if (dis[v][0] > cur.t + w) {
        dis[v][1] = dis[v][0], cnt[v][1] = cnt[v][0];
        dis[v][0] = cur.t + w, cnt[v][0] = cnt[cur.u][cur.type];
        pq.push({dis[v][1], v, 1});
        pq.push({dis[v][0], v, 0});
      } else if (dis[v][0] == cur.t + w) {
        cnt[v][0] += cnt[cur.u][cur.type];
      } else if (dis[v][1] > cur.t + w) {
        dis[v][1] = cur.t + w, cnt[v][1] = cnt[cur.u][cur.type];
        pq.push({dis[v][1], v, 1});
      } else if (dis[v][1] == cur.t + w) {
        cnt[v][1] += cnt[cur.u][cur.type];
      }
    }
  }

  int res = cnt[t][0];
  if (dis[t][1] - 1 == dis[t][0]) res += cnt[t][1];

  return res;
}

void process() {
  input();
  std::cout << Dijkstra() << "\n";
}

int main() {
  for (std::cin >> T; T; --T)
    process();
  return 0;
}
