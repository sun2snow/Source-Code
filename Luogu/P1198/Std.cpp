#include <bits/stdc++.h>
using lint = long long;
const int N = 2e5 + 10;

int lst; // 上一次询问的答案
int len; // 当前数列的长度
int Q, MOD;

struct SegmentTree {
  int max[N << 2];

  bool inRange(int l, int r, int L, int R) {
    return L <= l && r <= R;
  }

  bool outRange(int l, int r, int L, int R) {
    return l > R || r < L;
  }

  void pushup(int u) {
    max[u] = std::max(max[u << 1], max[u << 1 | 1]);
  }

  void update(int u, int l, int r, int pos, lint x) {
    if (l == r) {
      max[u] = x;
      return ;
    }
    int mid = l + r >> 1;
    if (pos <= mid) update(u << 1, l, mid, pos, x);
    else update(u << 1 | 1, mid + 1, r, pos, x);
    pushup(u);
  }

  lint query(int u, int l, int r, int L, int R) {
    if (outRange(l, r, L, R)) return LLONG_MIN;
    if (inRange(l, r, L, R)) return max[u];
    int mid = l + r >> 1;
    return std::max(query(u << 1, l, mid, L, R), query(u << 1 | 1, mid + 1, r, L, R));
  }
} Sgt;

int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cin >> Q >> MOD;
  for (int i = 0; i < Q; ++i) {
    lint x; char op;
    std::cin >> op >> x;
    
    if (op == 'A') { // 加入一个数
      // std::cerr << "add " << (x + lst) % MOD << std::endl;
      Sgt.update(1, 1, Q, ++len, (x + lst) % MOD);
    } else { // 查询 [len-L+1,len] 的最大值
      std::cout << (lst = Sgt.query(1, 1, Q, len - x + 1, len)) << "\n";
    }
  }
  std::cout.flush();
  return 0;
}
