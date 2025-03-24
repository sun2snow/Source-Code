#include <bits/stdc++.h>

int n, ans;

int main() {
  std::cin >> n;
  for (int a; n; --n) {
    std::cin >> a;
    ans ^= a;
  }
  std::cout << (ans ? "Yes\n" : "No\n");
  return 0;
}
