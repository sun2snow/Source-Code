#include <bits/stdc++.h>
const int N = 1e3 + 10;

int n, ans, a[N], f[N], g[N];

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  for (int i = 1; i <= n; ++i) {
    f[i] = 1;
    for (int j = 1; j < i; ++j)
      if (a[j] < a[i]) f[i] = std::max(f[i], f[j] + 1);
  }
  for (int i = n; i; --i) {
    g[i] = 1;
    for (int j = i + 1; j <= n; ++j)
      if (a[i] > a[j]) g[i] = std::max(g[i], g[j] + 1);
  }
  for (int i = 1; i <= n; ++i)
    ans = std::max(ans, f[i] + g[i] - 1);
  std::cout << ans << std::endl;
  return 0;
}
