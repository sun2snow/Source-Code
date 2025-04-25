#include <bits/stdc++.h>
using lint = long long;
const int N = 1e5 + 10;

int n, m;
lint a[N];

struct BinaryIndexedTree {
#define lowbit(i) ((i)&(-(i)))
  lint w[N], iw[N];
  void add(lint *arr, int pos, lint x) {
    for (int i = pos; i <= n; i += lowbit(i))
      arr[i] += x;
  }
  void update(int l, int r, lint x) {
    add(w, l, x);
    add(iw, l, x * l);
    if (r + 1 <= n) {
      add(w, r + 1, -x);
      add(iw, r + 1, -(r + 1) * x);
    }
  }
  lint sum(lint *arr, int u) {
    lint res = 0;
    for (int i = u; i; i -= lowbit(i)) res += arr[i];
    return res;
  }
  lint ask(int u) {
    return (u + 1) * sum(w, u) - sum(iw, u);
  }
  lint query(int l, int r) {
    return ask(r) - ask(l - 1);
  }
  void build() {
    for (int i = 1; i <= n; ++i) {
      add(w, i, a[i] - a[i - 1]);
      add(iw, i, (a[i] - a[i - 1]) * i);
    }
  }
} Bit;

signed main() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  Bit.build();
  for (char op; m; --m) {
    std::cin >> op;
    if (op == 'C') {
      int l, r, x;
      std::cin >> l >> r >> x;
      Bit.update(l, r, x);
    } else {
      int l, r;
      std::cin >> l >> r;
      std::cout << Bit.query(l, r) << "\n";
    }
  }
  return 0;
}
