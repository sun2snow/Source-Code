#include <bits/stdc++.h>
using lint = long long;
const int N = 20;

int m;
lint n, ans, p[N];

int main() {
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) std::cin >> p[i];
  for (int i = 1, cnt; i < 1 << m; ++i) {
    lint mul = 1;
    bool flag = true;
    cnt = 0;
    for (int j = 0; j < m; ++j)
      if (i >> j & 1) {
        ++cnt;
        mul *= p[j];
        if (mul > n) {
          flag = false;
          break;
        }
      }

    if (flag) {
      if (cnt & 1) {
        ans += n / mul;
      } else {
        ans -= n / mul;
      }
    }
  }

  std::cout << ans << std::endl;
  return 0;
}
