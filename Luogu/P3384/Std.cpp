#include <bits/stdc++.h>
using lint = long long;
const int N = 1e5 + 10;

std::vector<int> g[N];
int n, m, root, MOD, a[N];
int cnt, fa[N], dep[N], siz[N], son[N], top[N], dfn[N], rnk[N]; // 树链剖分数组

void dfs1(int u, int f) {
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (auto v : g[u]) {
    if (v == f) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int ftop) {
  top[u] = ftop, dfn[u] = ++cnt, rnk[cnt] = u;
  if (son[u]) dfs2(son[u], ftop);
  for (auto v : g[u])
    if (v != fa[u] && v != son[u]) dfs2(v, v);
}

struct SegmentTee {
  lint sum[N << 2], lzy[N << 2];
  bool outRange(int l, int r, int L, int R) {
    return l > R || r < L;
  }
  bool inRange(int l, int r, int L, int R) {
    return L <= l && r <= R;
  }
  void maketag(int u, int l, int r, lint x) {
    lzy[u] += x;
    (sum[u] += (r - l + 1) * x) %= MOD;
  }
  void pushup(int u) {
    sum[u] = (sum[u << 1] + sum[u << 1 | 1]) % MOD;
  }
  void pushdown(int u, int l, int r) {
    int mid = l + r >> 1;
    maketag(u << 1, l, mid, lzy[u]);
    maketag(u << 1 | 1, mid + 1, r, lzy[u]);
    lzy[u] = 0;
  }
  void build(int u, int l, int r) {
    if (l == r) {
      sum[u] = a[rnk[l]];
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
    return (query(u << 1, l, mid, L, R) + query(u << 1 | 1, mid + 1, r, L, R)) % MOD;
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

void update(int u, int v, lint x) { // 将 u-v 的路径 +x
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    Sgt.update(1, 1, n, dfn[top[u]], dfn[u], x);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  Sgt.update(1, 1, n, dfn[v], dfn[u], x);
}

lint query(int u, int v) { // 查询 u-v 的和
  lint res = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    (res += Sgt.query(1, 1, n, dfn[top[u]], dfn[u])) %= MOD;
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  (res += Sgt.query(1, 1, n, dfn[v], dfn[u])) %= MOD;
  return res;
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m >> root >> MOD;
  for (int i = 1; i <= n; ++i) std::cin >> a[i], a[i] %= MOD;
  for (int i = 1, u, v; i < n; ++i) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(root, 0);
  dfs2(root, root);

  Sgt.build(1, 1, n);
  for (int op, x, y, z; m; --m) {
    std::cin >> op >> x;
    if (op == 1) {
      std::cin >> y >> z;
      update(x, y, z % MOD);
    } else if (op == 2) {
      std::cin >> y;
      std::cout << query(x, y) << "\n";
    } else if (op == 3) {
      std::cin >> y;
      Sgt.update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, y % MOD);
    } else {
      std::cout << Sgt.query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1) << "\n";
    }
  }
  std::cout.flush();
  return 0;
}
