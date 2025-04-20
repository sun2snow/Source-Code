#include <bits/stdc++.h>
const int N = 5e5 + 10;

int n, m, a[N];

struct SegmentTree {
  struct Node {
    int sum, lmax, rmax, max;
  };

  int sum[N << 2], lmax[N << 2], rmax[N << 2], max[N << 2];

  bool outRange(int l, int r, int L, int R) {
    return l > R || r < L;
  }

  bool inRange(int l, int r, int L, int R) {
    return L <= l && r <= R;
  }

  void pushup(int u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
    lmax[u] = std::max(lmax[u << 1], sum[u << 1] + lmax[u << 1 | 1]);
    rmax[u] = std::max(rmax[u << 1 | 1], sum[u << 1 | 1] + rmax[u << 1]);
    max[u] = std::max({max[u << 1], max[u << 1 | 1], rmax[u << 1] + lmax[u << 1 | 1]});
  }

  void build(int u, int l, int r) {
    if (l == r) {
      sum[u] = a[l];
      lmax[u] = rmax[u] = max[u] = a[l];
      return ;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
  }

  Node query(int u, int l, int r, int L, int R) {
    if (outRange(l, r, L, R)) return {0, (int)-1e9, (int)-1e9, (int)-1e9};
    if (inRange(l, r, L, R)) return {sum[u], lmax[u], rmax[u], max[u]};
    int mid = l + r >> 1;
    auto lson = query(u << 1, l, mid, L, R);
    auto rson = query(u << 1 | 1, mid + 1, r, L, R);
    Node res;
    res.sum = lson.sum + rson.sum;
    res.lmax = std::max(lson.lmax, lson.sum + rson.lmax);
    res.rmax = std::max(rson.rmax, rson.sum + lson.rmax);
    res.max = std::max({lson.max, rson.max, lson.rmax + rson.lmax});
    return res;
  }

  void update(int u, int l, int r, int pos, int x) {
    if (l == r) {
      sum[u] = x;
      lmax[u] = rmax[u] = max[u] = x;
      return ;
    }
    int mid = l + r >> 1;
    if (pos <= mid) update(u << 1, l, mid, pos, x);
    else update(u << 1 | 1, mid + 1, r, pos, x);
    pushup(u);
  }
} Sgt;

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  Sgt.build(1, 1, n);
  for (int op, x, y; m; --m) {
    std::cin >> op >> x >> y;
    if (op == 1) {
      if (x > y) std::swap(x, y);
      std::cout << Sgt.query(1, 1, n, x, y).max << "\n";
    } else {
      Sgt.update(1, 1, n, x, y);
    }
  }
  std::cout.flush();
  return 0;
}
