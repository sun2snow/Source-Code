#include <bits/stdc++.h>
const int N = 1e5 + 10;

int n, m;

struct SegmentTree {
  int sum[N << 2], lzy[N << 2];

  bool outRange(int l, int r, int L, int R) {
    return l > R || r < L;
  }
  bool inRange(int l, int r, int L, int R) {
    return L <= l && r <= R;
  }
  void maketag(int u, int l, int r) {
    lzy[u] ^= 1, sum[u] = r - l + 1 - sum[u];
  }
  void pushup(int u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
  }
  void pushdown(int u, int l, int r) {
    if (lzy[u]) {
      int mid = l + r >> 1;
      maketag(u << 1, l, mid);
      maketag(u << 1 | 1, mid + 1, r);
      lzy[u] = 0;
    }
  }
  int query(int u, int l, int r, int pos) {
    if (l == r) return sum[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    if (pos <= mid) return query(u << 1, l, mid, pos);
    return query(u << 1 | 1, mid + 1, r, pos);
  }
  void update(int u, int l, int r, int L, int R) {
    if (outRange(l, r, L, R)) return ;
    if (inRange(l, r, L, R)) {
      maketag(u, l, r);
      return ;
    }
    int mid = l + r >> 1;
    pushdown(u, l, r);
    update(u << 1, l, mid, L, R);
    update(u << 1 | 1, mid + 1, r, L, R);
    pushup(u);
  }
} Sgt;

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m;
  for (int op, x, y; m; --m) {
    std::cin >> op >> x;
    if (op == 1) {
      std::cin >> y;
      Sgt.update(1, 1, n, x, y);
    } else {
      std::cout << Sgt.query(1, 1, n, x) << "\n";
    }
  }
  std::cout.flush();
  return 0;
}
