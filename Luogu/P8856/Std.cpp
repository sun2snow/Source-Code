#include <bits/stdc++.h>
const int N = 6e4 + 10;

int n, m, k;

struct SegmentTree {
  int min[N << 2], lzy[N << 2];
  
  bool outRange(int l, int r, int L, int R) {
    return l > R || r < L;
  }

  bool inRange(int l, int r, int L, int R) {
    return L <= l && r <= R;
  }

  void maketag(int u, int x) {
    min[u] += x, lzy[u] += x;
  }

  void pushup(int u) {
    min[u] = std::min(min[u << 1], min[u << 1 | 1]);
  }

  void pushdown(int u) {
    maketag(u << 1, lzy[u]);
    maketag(u << 1 | 1, lzy[u]);
    lzy[u] = 0;
  }

  void build(int u, int l, int r, int x) {
    if (l == r) {
      min[u] = x, lzy[u] = 0;
      return ;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid, x);
    build(u << 1 | 1, mid + 1, r, x);
    pushup(u);
  }

  int query(int u, int l, int r, int L, int R) {
    if (outRange(l, r, L, R)) return 2e9;
    if (inRange(l, r, L, R)) return min[u];
    int mid = l + r >> 1;
    pushdown(u);
    return std::min(query(u << 1, l, mid, L, R), query(u << 1 | 1, mid + 1, r, L, R));
  }

  void update(int u, int l, int r, int L, int R, int x) {
    if (outRange(l, r, L, R)) return ;
    if (inRange(l, r, L, R)) {
      maketag(u, x);
      return ;
    }
    int mid = l + r >> 1;
    pushdown(u);
    update(u << 1, l, mid, L, R, x);
    update(u << 1 | 1, mid + 1, r, L, R, x);
    pushup(u);
  }
} Sgt;

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> k >> m;
  Sgt.build(1, 1, n - 1, k);
  for (int l, r, x; m; --m) {
    std::cin >> l >> r >> x;
    // std::cout << Sgt.query(1, 1, n, l, r) << "\n";
    if (Sgt.query(1, 1, n - 1, l, r - 1) >= x) {
      Sgt.update(1, 1, n - 1, l, r - 1, -x);
      std::cout << "T\n";
    } else std::cout << "N\n";
  }
  std::cout.flush();
  return 0;
}
