#include <bits/stdc++.h>
const int N = 1e5 + 10;

int n, a[N], ans[N];

struct BinaryIndexedTree {
#define lowbit(i) ((i)&(-(i)))
  int w[N];
  void add(int pos, int x) {
    for (int i = pos; i <= n; i += lowbit(i))
      w[i] += x;
  }
  void build() {
    for (int i = 1; i <= n; ++i) w[i] = lowbit(i);
  }
  int query(int x) { // 找到最小的 i 使得 sum(1, i) >= x
    // 找到最小的 j 使得 sum(1, j) < x，则 i=j+1
    int sum = 0, p = 0;
    for (int i = std::__lg(n); ~i; --i) {
      p += 1 << i;
      if (p >= n || sum + w[p] >= x) p -= 1 << i;
      else sum += w[p];
    }
    return p + 1;
  }
} Bit;

int main() {
  std::cin >> n;
  for (int i = 2; i <= n; ++i) std::cin >> a[i];
  Bit.build();
  for (int i = n; i; --i) {
    ans[i] = Bit.query(a[i] + 1);
    Bit.add(ans[i], -1);
  }
  for (int i = 1; i <= n; ++i) std::cout << ans[i] << "\n";
  return 0;
}
