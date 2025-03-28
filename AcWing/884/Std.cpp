#include <bits/stdc++.h>
const int N = 1e2 + 10;

int n, res, a[N][N];

int gauss() {
  int r, c;
  for (r = c = 0; c < n; ++c) {
    int t = -1;
    for (int i = r; i < n; ++i)
      if (a[i][c]) {
        t = i;
        break;
      }
    if (t == -1) continue;
    for (int i = c; i <= n; ++i)
      std::swap(a[t][i], a[r][i]);
    for (int i = r + 1; i < n; ++i)
      if (a[i][c])
        for (int j = n; j >= c; --j)
          a[i][j] ^= a[r][j];
    ++r;
  }

  if (r < n) {
    for (int i = r; i < n; ++i)
      if (a[i][n]) return 2;
    return 1;
  }

  for (int i = n - 2; ~i; --i)
    for (int j = i + 1; j < n; ++j)
      a[i][n] ^= a[i][j] & a[j][n];
  
  return 0;
}

int main() {
  std::cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j <= n; ++j)
      std::cin >> a[i][j];
  int res = gauss();
  if (res == 0) {
    for (int i = 0; i < n; ++i)
      std::cout << a[i][n] << "\n";
  } else if (res == 1) {
    puts("Multiple sets of solutions");
  } else {
    puts("No solution");
  }
  return 0;
}
