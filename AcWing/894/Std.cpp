#include <bits/stdc++.h>
const int N = 110;

int n, res, f[N];

int sg(int x) {
  if (~f[x]) return f[x];
  std::unordered_set<int> S;
  for (int i = 0; i < x; ++i)
    for (int j = 0; j <= i; ++j)
      S.insert(sg(i) ^ sg(j));
  for (int i = 0; ; ++i)
    if (S.find(i) == S.end()) return f[x] = i;
  return f[x] = -2;
}

int main() {
  std::cin >> n;
  memset(f, -1, sizeof(f));
  for (int i = 0, a; i < n; ++i)
    std::cin >> a, res ^= sg(a);
  if (res) puts("Yes");
  else puts("No");
  return 0;
}
