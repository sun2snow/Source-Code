#include <bits/stdc++.h>
const int N = 1e6 + 10, V = 1e9 + 10;

int n, m, ans = 2e9;
struct Segment {
  int l, r;
  int dl, dr;

  bool operator<(const Segment &e) const {
    return r - l < e.r - e.l;
  }
} a[N];

std::vector<int> num; // 离散化数组

struct SegmentTree {
  struct TreeNode {
    int max, lzy;
    TreeNode *lson, *rson;
    TreeNode() : max(0), lzy(0), lson(nullptr), rson(nullptr) {}
  } *root;

  bool outRange(int l, int r, int ql, int qr) {
    return ql > qr || l > qr || r < ql;
  }
  bool inRange(int l, int r, int ql, int qr) {
    return ql <= l && r <= qr;
  }
  void maketag(TreeNode *u, int x) {
    u->max += x;
    u->lzy += x;
  }
  void pushup(TreeNode *u) {
    u->max = std::max(u->lson->max, u->rson->max);
  }
  void pushdown(TreeNode *u) {
    if (!u->lson) u->lson = new TreeNode();
    if (!u->rson) u->rson = new TreeNode();
    maketag(u->lson, u->lzy);
    maketag(u->rson, u->lzy);
    u->lzy = 0;
  }
  void build() {
    root = new TreeNode();
  }
  void update(TreeNode *u, int l, int r, int ql, int qr, int x) {
    if (outRange(l, r, ql, qr)) return ;
    if (inRange(l, r, ql, qr)) {
      maketag(u, x);
      return ;
    }
    int mid = l + r >> 1;
    pushdown(u);
    update(u->lson, l, mid, ql, qr, x);
    update(u->rson, mid + 1, r, ql, qr, x);
    pushup(u);
  }
} Sgt;

void discrete() {
  std::sort(num.begin(), num.end());
  num.erase(std::unique(num.begin(), num.end()), num.end());
  for (int i = 1; i <= n; ++i) {
    a[i].dl = std::lower_bound(num.begin(), num.end(), a[i].l) - num.begin() + 1;
    a[i].dr = std::lower_bound(num.begin(), num.end(), a[i].r) - num.begin() + 1;
  }
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i].l >> a[i].r, ++a[i].l, ++a[i].r;
    num.push_back(a[i].l), num.push_back(a[i].r);
  }
  discrete();
  std::sort(a + 1, a + n + 1);
  Sgt.build();
  // for (int i = 1; i <= n; ++i) {
  //   std::cout << "[" << a[i].l << ", " << a[i].r << "]" << " (" << a[i].dl << ", " << a[i].dr << ")\n";
  // }
  for (int i = 1, j = 0; i <= n && j <= n; ++i) {
    while (j + 1 <= n && Sgt.root->max < m) {
      ++j;
      Sgt.update(Sgt.root, 1, num.back(), a[j].dl, a[j].dr - 1, 1);
    }
    if (Sgt.root->max < m) break;
    ans = std::min(ans, a[j].r - a[j].l - (a[i].r - a[i].l));
    Sgt.update(Sgt.root, 1, num.back(), a[i].dl, a[i].dr - 1, -1);
  }
  std::cout << (ans == (int)2e9 ? -1 : ans) << std::endl;
  return 0;
}
