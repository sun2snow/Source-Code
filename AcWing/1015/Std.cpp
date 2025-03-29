#include <bits/stdc++.h>
const int N = 1e2 + 10;

int T, n, m, w[N][N], f[N][N];

int main() {
  for (std::cin >> T; T; --T) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        std::cin >> w[i][j];
    
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        f[i][j] = std::max(f[i - 1][j], f[i][j - 1]) + w[i][j];
    
    std::cout << f[n][m] << std::endl;
  }
  return 0;
}
