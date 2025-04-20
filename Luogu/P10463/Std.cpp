#include <bits/stdc++.h>
using lint = long long;
const int N = 5e5 + 10;

int n, m;
lint a[N], b[N];

struct BinaryIndexedTree {
#define lowbit(i) ((i)&(-(i)))
  lint w[N];

  void build() {
    for (int i = 1; i <= n; ++i)
      update(i, b[i]);
  }

  void update(int pos, lint x) { // 第 pos 位 +x
    for (int i = pos; i <= n; i += lowbit(i))
      w[i] += x;
  }

  lint query(int pos) {
    lint res = 0;
    for (int i = pos; i; i -= lowbit(i))
      res += w[i];
    return res;
  }
} Bit;

struct SegmentTree {
  lint gcd[N << 2];

  bool inRange(int l, int r, int L, int R) {
    return L <= l && r <= R;
  }

  void pushup(int u) {
    gcd[u] = std::__gcd(gcd[u << 1], gcd[u << 1 | 1]);
  }

  void build(int u, int l, int r) {
    if (l == r) {
      gcd[u] = b[l];
      return ;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
  }

  lint query(int u, int l, int r, int L, int R) {
    if (inRange(l, r, L, R)) return gcd[u];
    int mid = l + r >> 1;
    if (R <= mid) return query(u << 1, l, mid, L, R);
    if (L > mid) return query(u << 1 | 1, mid + 1, r, L, R);
    return std::__gcd(query(u << 1, l, mid, L, R), 
                      query(u << 1 | 1, mid + 1, r, L, R));
  }

  void update(int u, int l, int r, int pos, lint x) {
    if (l == r) {
      gcd[u] += x;
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
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i], b[i] = a[i] - a[i - 1];
  Bit.build();
  Sgt.build(1, 1, n);

  for (char op; m; --m) {
    int l, r; lint x;
    std::cin >> op >> l >> r;
    if (op == 'C') {
      std::cin >> x;
      Sgt.update(1, 1, n, l, x), Bit.update(l, x);
      if (r + 1 <= n) Sgt.update(1, 1, n, r + 1, -x), Bit.update(r + 1, -x);
    } else {
      if (l == r) std::cout << Bit.query(l) << "\n";
      else std::cout << llabs(std::__gcd(Bit.query(l), Sgt.query(1, 1, n, l + 1, r))) << "\n";
      // Sgt.query(1, 1, n, l + 1, r);
    }
  }
  std::cout.flush();
  return 0;
}
