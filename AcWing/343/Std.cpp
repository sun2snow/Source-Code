#include <bits/stdc++.h>
const int N = 30;

bool vis[N];
int n, m, g[N][N];

void update(int u, int v) { // 新加入了 u->v 这一条边，更新传递闭包
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      if (g[x][u]) g[x][v] = 1;
      if (g[v][y]) g[u][y] = 1;
      g[x][y] |= g[x][u] & g[v][y];
    }
  }
}

int check() { // 无法确定返回 0，矛盾返回 1，成功返回 2
  for (int i = 0; i < n; ++i)
    if (g[i][i]) return 1;


  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      if (i != j && !(g[i][j] | g[j][i])) return 0;
    }
  
  return 2;
}

char get_ch() {
  for (int i = 0; i < n; ++i) {
    if (vis[i]) continue;
    bool flag = true;
    for (int j = 0; j < n; ++j) {
      if (vis[j]) continue;
      if (g[j][i]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      vis[i] = true;
      return i + 'A';
    }
  }
  return 0;
}

void print(int a[][N]) {
  puts("-------print begin-------");

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      std::cout << a[i][j] << " \n"[j == n - 1];
  }

  puts("------print finish-------");
}

void process() {
  memset(g, 0, sizeof(g));
  memset(vis, 0, sizeof(vis));

  int type = 0, t;
  std::string s;
  for (int i = 1; i <= m; ++i) {
    std::cin >> s;
    int u = s[0] - 'A', v = s[2] - 'A';
    if (!type) {
      g[u][v] = 1;
      update(u, v);
      type = check();
      if (type) t = i;
    }

    // print(g);
  }

  if (type == 1) {
    printf("Inconsistency found after %d relations.\n", t);
  } else if (type == 2) {
    printf("Sorted sequence determined after %d relations: ", t);
    for (int i = 0; i < n; ++i) std::cout << get_ch();
    puts(".");
  } else {
    puts("Sorted sequence cannot be determined.");
  }
}

int main() {
  while (std::cin >> n >> m, n || m) process();
  return 0;
}
