#include <bits/stdc++.h>

int n, a, res;

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a;
    if (i & 1) res ^= a;
  }
  if (res) puts("Yes");
  else puts("No");
  return 0;
}
