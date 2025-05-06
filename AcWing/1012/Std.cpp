#include <bits/stdc++.h>
using pii = std::pair<int, int>;
const int N = 5e3 + 10;

pii a[N];
int n, f[N];

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> a[i].first >> a[i].second;
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) {
    f[i] = 1;
    for (int j = 1; j < i; ++j)
      if (a[j].second < a[i].second) f[i] = std::max(f[i], f[j] + 1);
  }
  std::cout << *std::max_element(f + 1, f + n + 1) << std::endl;
  return 0;
}
