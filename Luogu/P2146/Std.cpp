#include <bits/stdc++.h>
const int N = 1e5 + 10;

int n, q;
std::vector<int> g[N];
int cnt, fa[N], dep[N], siz[N], son[N], top[N], dfn[N], rnk[N]; // 树链剖分

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
  int query(int u, int l, int r, int ql, int qr) {
    if (outRange(l, r, ql, qr)) return 0;
    if (inRange(l, r, ql, qr)) return sum[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    return query(u << 1, l, mid, ql, qr) + query(u << 1 | 1, mid + 1, r, ql, qr);
  }
  void update(int u, int l, int r, int ql, int qr, int x) {
    if (outRange(l, r, ql, qr)) return ;
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

int query(int u, int v) { // 查询 u-v 之间 1 的个数
  int res = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    res += Sgt.query(1, 1, n, dfn[top[u]], dfn[u]);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  res += Sgt.query(1, 1, n, dfn[v], dfn[u]);
  return res;
}

void update(int u, int v) { // 将 u-v 更新为 1
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    Sgt.update(1, 1, n, dfn[top[u]], dfn[u], 1);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  Sgt.update(1, 1, n, dfn[v], dfn[u], 1);
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n;
  for (int i = 2, x; i <= n; ++i) {
    std::cin >> x, ++x;
    g[x].push_back(i);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  memset(Sgt.lzy, -1, sizeof(Sgt.lzy));
  for (std::cin >> q; q; --q) {
    std::string op; int x;
    std::cin >> op >> x, ++x;
    if (op[0] == 'i') { // 0-x 的路径需要赋值为 1
      std::cout << dep[x] - query(1, x) << "\n";
      update(1, x);
    } else {
      std::cout << Sgt.query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1) << "\n";
      Sgt.update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, 0);
    }
  }
  std::cout.flush();
  return 0;
}
