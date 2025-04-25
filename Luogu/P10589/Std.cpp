#include <bits/stdc++.h>
using lint = long long;
const int N = 2e5 + 10;

lint ans1, ans2;
int n, a[N], b[N][2], c[N][2];
// a[i] 记录 y，b[i][0/1] 记录左/右边小于 a[i] 的，c[i][0/1] 记录左/右边大于 a[i] 的。

struct BinaryIndexedTree {
#define lowbit(i) ((i)&(-(i)))
  int w[N];
  void clear() {
    memset(w, 0, sizeof(w));
  }
  int ask(int pos) {
    int res = 0;
    for (int i = pos; i; i -= lowbit(i)) res += w[i];
    return res;
  }
  int query(int l, int r) {
    return ask(r) - ask(l - 1);
  }
  void update(int pos, int x) {
    for (int i = pos; i <= n; i += lowbit(i)) w[i] += x;
  }
} Bit;

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  for (int i = 1; i <= n; ++i) {
    b[i][0] = Bit.query(1, a[i] - 1);
    c[i][0] = Bit.query(a[i] + 1, n);
    Bit.update(a[i], 1);
  }
  Bit.clear();
  for (int i = n; i; --i) {
    b[i][1] = Bit.query(1, a[i] - 1);
    c[i][1] = Bit.query(a[i] + 1, n);
    Bit.update(a[i], 1);
  }
  for (int i = 1; i <= n; ++i) {
    ans1 += 1ll * b[i][0] * b[i][1];
    ans2 += 1ll * c[i][0] * c[i][1];
  }
  std::cout << ans2 << " " << ans1 << std::endl;
  return 0;
}
