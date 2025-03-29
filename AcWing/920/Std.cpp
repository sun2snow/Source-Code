#include <bits/stdc++.h>
const int N = 510;

bool vis[N];
int n, m, dis[N];
std::queue<int> q;
std::vector<int> g[N];

void bfs() {
  q.push(1);
  vis[1] = true;
  memset(dis, 0x3f, sizeof(dis));
  dis[1] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (auto v : g[u]) {
      if (vis[v]) continue;

      dis[v] = dis[u] + 1;
      vis[v] = true;
      q.push(v);
    }
  }
}

int main() {
  std::cin >> m >> n;
  getchar();
  for (int i = 1; i <= m; ++i) {
    std::string tmp_s;
    std::getline(std::cin, tmp_s);
    std::stringstream ss(tmp_s);

    std::vector<int> a;
    int x;
    while (ss >> x) a.push_back(x);
    for (int p = 0; p < a.size(); ++p)
      for (int q = p + 1; q < a.size(); ++q)
        g[a[p]].push_back(a[q]);
  }

  // for (int i = 1; i <= n; ++i) {
  //   for (auto v : g[i])
  //     std::cout << v << " ";
  //   std::cout << std::endl;
  // }

  bfs();

  if (dis[n] == 0x3f3f3f3f) std::cout << "NO\n";
  else std::cout << std::max(dis[n] - 1, 0) << std::endl;
  return 0;
}
