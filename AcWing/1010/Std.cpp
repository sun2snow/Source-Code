#include <bits/stdc++.h>
const int N = 1e3 + 10;

int n, a[N], f[N], g[N];

int main() {
  int x;
  while (std::cin >> x) a[++n] = x;
  for (int i = 1; i <= n; ++i) {
    f[i] = 1;
    for (int j = 1; j < i; ++j)
      if (a[j] < a[i]) f[i] = std::max(f[i], f[j] + 1);
  }
  for (int i = 1; i <= n; ++i) {
    g[i] = 1;
    for (int j = 1; j < i; ++j)
      if (a[j] >= a[i]) g[i] = std::max(g[i], g[j] + 1);
  }
  std::cout << *std::max_element(g + 1, g + n + 1) << std::endl << *std::max_element(f + 1, f + n + 1) << std::endl;
  return 0;
}
