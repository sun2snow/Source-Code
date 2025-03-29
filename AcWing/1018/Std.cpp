#include <bits/stdc++.h>
const int N = 1e2 + 10;

int n, w[N][N], f[N][N];

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      std::cin >> w[i][j];

  memset(f, 0x3f, sizeof(f));
  f[0][1] = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      f[i][j] = std::min(f[i - 1][j], f[i][j - 1]) + w[i][j];
  
  std::cout << f[n][n] << std::endl;
  return 0;
}
