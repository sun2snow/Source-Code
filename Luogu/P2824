#include <bits/stdc++.h>

// #define DEBUG

const int N = 1e5 + 10;

struct Operation {
  int op, l, r;
} Q[N];

int l, r; // 二分
int n, m, pos, a[N];

struct SegmentTree {
  int sum[N << 2], lzy[N << 2];
  bool outRange(int l, int r, int ql, int qr) {
    return l > qr || r < ql;
  }
  bool inRange(int l, int r, int ql, int qr) {
    return ql <= l && r <= qr;
  }
  void maketag(int u, int l, int r, int x) {
    lzy[u] = x;
    if (x) sum[u] = r - l + 1;
    else sum[u] = 0;
  }
  void pushup(int u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
  }
  void pushdown(int u, int l, int r) {
    if (lzy[u] != -1) {
      int mid = l + r >> 1;
      maketag(u << 1, l, mid, lzy[u]);
      maketag(u << 1 | 1, mid + 1, r, lzy[u]);
      lzy[u] = -1;
    }
  }
  void build(int u, int l, int r, int x) {
    lzy[u] = -1;
    if (l == r) {
      sum[u] = (a[l] > x);
      return ;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid, x);
    build(u << 1 | 1, mid + 1, r, x);
    pushup(u);
  }
  int query(int u, int l, int r, int ql, int qr) {
    if (ql > qr || outRange(l, r, ql, qr)) return 0;
    if (inRange(l, r, ql, qr)) return sum[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    return query(u << 1, l, mid, ql, qr) + query(u << 1 | 1, mid + 1, r, ql, qr);
  }
  void update(int u, int l, int r, int ql, int qr, int x) {
    if (ql > qr || outRange(l, r, ql, qr)) return ;
    if (inRange(l, r, ql, qr)) {
      maketag(u, l, r, x);
      return ;
    }
    int mid = l + r >> 1;
    pushdown(u, l, r);
    update(u << 1, l, mid, ql, qr, x);
    update(u << 1 | 1, mid + 1, r, ql, qr, x);
    pushup(u);
  }
} Sgt;

bool check(int x) {
  Sgt.build(1, 1, n, x);

#ifdef DEBUG
  for (int i = 1; i <= n; ++i)
    std::cout << Sgt.query(1, 1, n, i, i) << " ";
  std::cout << "\n";
#endif

  for (int i = 1; i <= m; ++i) {
    int op = Q[i].op, l = Q[i].l, r = Q[i].r;
    int cnt1 = Sgt.query(1, 1, n, l, r);
    int cnt0 = r - l + 1 - cnt1;

    if (op == 0) {
      Sgt.update(1, 1, n, l, l + cnt0 - 1, 0);
      Sgt.update(1, 1, n, l + cnt0, r, 1);
    } else {
      Sgt.update(1, 1, n, l, l + cnt1 - 1, 1);
      Sgt.update(1, 1, n, l + cnt1, r, 0);
    }

#ifdef DEBUG
    for (int i = 1; i <= n; ++i)
      std::cout << Sgt.query(1, 1, n, i, i) << " ";
    std::cout << "\n";
#endif

  }
  return Sgt.query(1, 1, n, pos, pos) == 0;
}

int main() {
#ifndef DEBUG
  std::cin.tie(0)->sync_with_stdio(0);
#endif
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  for (int i = 1; i <= m; ++i) std::cin >> Q[i].op >> Q[i].l >> Q[i].r;
  std::cin >> pos;

  l = -1, r = n + 2;
  while (l + 1 != r) {
    int mid = l + r >> 1;
    if (check(mid)) r = mid;
    else l = mid;
  }
  // std::cout << check(5) << "\n";

  std::cout << r << std::endl;
  return 0;
}
