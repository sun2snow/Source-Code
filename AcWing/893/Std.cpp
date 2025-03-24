#include <bits/stdc++.h>
const int N = 1e2 + 10, M = 1e4 + 10;

int n, m, ans, a[N], f[M];

int sg(int x) {
  if (f[x] != -1) return f[x];

  std::unordered_set<int> set;
  for (int i = 1; i <= n; ++i)
    if (x >= a[i]) set.insert(sg(x - a[i]));
  for (int i = 0; ; ++i)
    if (set.find(i) == set.end()) return f[x] = i;
  return f[x] = -1;
}

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  memset(f, -1, sizeof(f));
  std::cin >> m;
  for (int i = 1, a; i <= m; ++i) {
    std::cin >> a;
    ans ^= sg(a);
  }
  std::cout << (ans ? "Yes\n" : "No\n");
  return 0;
}
