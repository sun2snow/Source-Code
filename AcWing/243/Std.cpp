#include <bits/stdc++.h>
using lint = long long;
const int N = 1e5 + 10;

int n, m;
lint a[N];

struct SegmentTree {
  lint sum[N << 2], lzy[N << 2];

  bool outRange(int l, int r, int L, int R) {
    return l > R || r < L;
  }

  bool inRange(int l, int r, int L, int R) {
    return L <= l && r <= R;
  }

  void pushup(int u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
  }

  void maketag(int u, int l, int r, lint x) {
    sum[u] += (r - l + 1) * x;
    lzy[u] += x;
  }

  void pushdown(int u, int l, int r) {
    int mid = l + r >> 1;
    maketag(u << 1, l, mid, lzy[u]);
    maketag(u << 1 | 1, mid + 1, r, lzy[u]);
    lzy[u] = 0;
  }

  void build(int u, int l, int r) {
    if (l == r) {
      sum[u] = a[l];
      return ;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
  }

  lint query(int u, int l, int r, int L, int R) {
    if (outRange(l, r, L, R)) return 0;
    if (inRange(l, r, L, R)) return sum[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    return query(u << 1, l, mid, L, R) + query(u << 1 | 1, mid + 1, r, L, R);
  }

  void update(int u, int l, int r, int L, int R, lint x) {
    if (outRange(l, r, L, R)) return ;
    if (inRange(l, r, L, R)) {
      maketag(u, l, r, x);
      return ;
    }
    int mid = l + r >> 1;
    pushdown(u, l, r);
    update(u << 1, l, mid, L, R, x);
    update(u << 1 | 1, mid + 1, r, L, R, x);
    pushup(u);
  }
} Sgt;

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  Sgt.build(1, 1, n);
  for (char op; m; --m) {
    int l, r; lint x;
    std::cin >> op >> l >> r;
    if (op == 'C') {
      std::cin >> x;
      Sgt.update(1, 1, n, l, r, x);
    } else {
      std::cout << Sgt.query(1, 1, n, l, r) << "\n";
    }
  }
  std::cout.flush();
  return 0;
}
