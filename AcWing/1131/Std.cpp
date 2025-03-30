#include <bits/stdc++.h>
const int N = 13, M = 1 << N;
const int dir[][2] = {0, 1, 1, 0, 0, -1, -1, 0};

struct Data { // 队列中存储的状态
  int x, y; // 坐标
  int state; // 钥匙的状态
};

int key[N][N]; // key[x][y] 表示 (x,y) 存储的钥匙。没有钥匙的话为 0。
int mp[N][N][N][N];
// mp[x1][y1][x2][y2] 表示 (x1,y1) 到 (x2,y2) 之间的阻隔，-1空地，0墙，>=1门
int dis[N][N][M]; // 表示到达的最少步数。没有到达过记为 -1

int n, m, p, k, s;

void init() {
  std::cin >> n >> m >> p >> k;
  memset(mp, -1, sizeof(mp));
  for (int i = 0, x1, y1, x2, y2, type; i < k; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2 >> type;
    mp[x1][y1][x2][y2] = mp[x2][y2][x1][y1] = type;
  }
  std::cin >> s;
  for (int i = 0, x, y, q; i < s; ++i) {
    std::cin >> x >> y >> q;
    key[x][y] |= 1 << q;
  }
}

void bfs() {
  std::queue<Data> q;
  q.push({1, 1, key[1][1]});
  memset(dis, -1, sizeof(dis));
  dis[1][1][key[1][1]] = 0;

  while (!q.empty()) {
    int x = q.front().x, y = q.front().y, st = q.front().state; q.pop();

    for (int i = 0; i < 4; ++i) {
      int fx = x + dir[i][0], fy = y + dir[i][1];
      int new_st = st | key[fx][fy];

      if (fx < 1 || fx > n || fy < 1 || fy > m) continue; // 越界
      if (~dis[fx][fy][new_st]) continue; // 访问过了
      if (mp[x][y][fx][fy] == 0) continue; // 墙
      if (mp[x][y][fx][fy] != -1 && ((st >> mp[x][y][fx][fy] & 1) == 0)) continue; // 门但是没有钥匙

      // 可以通过，到达 (fx, fy)
      dis[fx][fy][new_st] = dis[x][y][st] + 1;
      q.push({fx, fy, new_st});

      if (fx == n && fy == m) {
        std::cout << dis[fx][fy][new_st] << std::endl;
        return ;
      }
    }
  }
  std::cout << -1 << std::endl;
}

int main() {
  init();
  bfs();
  return 0;
}
