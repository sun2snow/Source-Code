#include <bits/stdc++.h>
const int N = 1e5 + 10;

int n, m, a[N];

struct BinaryIndexedTree {
#define lowbit(i) ((i)&(-(i)))
  int w[N];
  void add(int pos, int x) {
    for (int i = pos; i <= n; i += lowbit(i)) w[i] += x;
  }
  int ask(int pos) {
    int res = 0;
    for (int i = pos; i; i -= lowbit(i)) res += w[i];
    return res;
  }
  void build() {
    for (int i = 1; i <= n; ++i)
      add(i, a[i] - a[i - 1]);
  }
} Bit;

int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  Bit.build();
  for (char op; m; --m) {
    std::cin >> op;
    if (op == 'C') {
      int l, r, x;
      std::cin >> l >> r >> x;
      Bit.add(l, x);
      if (r + 1 <= n) Bit.add(r + 1, -x);
    } else {
      int x;
      std::cin >> x;
      std::cout << Bit.ask(x) << "\n";
    }
  }
  return 0;
}
