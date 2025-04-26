#include <bits/stdc++.h>
const int N = 1e5 + 10;

int n, a[N], ans[N];

struct SegmentTree {
  int sum[N << 2];
  void pushup(int u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
  }
  void build(int u, int l, int r) {
    if (l == r) {
      sum[u] = 1;
      return ;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
  }
  void add(int u, int l, int r, int pos, int x) {
    if (l == r) {
      sum[u] += x;
      return ;
    }
    int mid = l + r >> 1;
    if (pos <= mid) add(u << 1, l, mid, pos, x);
    else add(u << 1 | 1, mid + 1, r, pos, x);
    pushup(u);
  }
  int query(int u, int l, int r, int k) {
    if (l == r) return l;
    int mid = l + r >> 1;
    if (k <= sum[u << 1]) return query(u << 1, l, mid, k);
    return query(u << 1 | 1, mid + 1, r, k - sum[u << 1]);
  }
} Sgt;

int main() {
  std::cin >> n;
  for (int i = 2; i <= n; ++i) std::cin >> a[i];
  Sgt.build(1, 1, n);
  for (int i = n; i; --i) {
    ans[i] = Sgt.query(1, 1, n, a[i] + 1);
    Sgt.add(1, 1, n, ans[i], -1);
  }
  for (int i = 1; i <= n; ++i) std::cout << ans[i] << "\n";
  return 0;
}
