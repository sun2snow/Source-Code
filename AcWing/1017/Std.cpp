#include <bits/stdc++.h>
const int N = 110;

int T, n, ans, a[N], f[N], g[N];

int main() {
  for (std::cin >> T; T; --T) {
    std::cin >> n, ans = 0;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) {
      f[i] = g[i] = 1;
      for (int j = 1; j < i; ++j) {
        if (a[j] < a[i]) f[i] = std::max(f[i], f[j] + 1);
        if (a[j] > a[i]) g[i] = std::max(g[i], g[j] + 1);
      }
    }
    for (int i = 1; i <= n; ++i)
      ans = std::max({ans, f[i], g[i]});
    std::cout << ans << std::endl;
  }
  return 0;
}
