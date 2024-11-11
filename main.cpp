#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;

string stats;
map<string, ll> visit{};

vl dx{-1, 1, 0, 0};
vl dy{0, 0, -1, 1};

ll Bfs() {
  queue<string> Q{};
  Q.push(stats);

  while (!Q.empty()) {
    auto f = Q.front();
    Q.pop();
    auto val = visit[f];

    auto idx = -1;
    for (auto i = 0; i < 9; ++i) {
      if (f[i] == '0') {
        idx = i;
        break;
      }
    }

    if (f == "123456780") return val;

    const auto& x = idx % 3;
    const auto& y = idx / 3;
    for (auto d = 0; d < 4; ++d) {
      const auto& nx = x + dx[d];
      const auto& ny = y + dy[d];

      if (nx < 0 || 3 <= nx || ny < 0 || 3 <= ny) continue;

      const auto& new_idx = nx + ny * 3;
      auto nf = f;
      std::swap(nf[idx], nf[new_idx]);

      if (visit.find(nf) != visit.end()) continue;

      visit.insert({nf, val + 1});
      Q.push(nf);
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto oss = ostringstream{};
  for (auto i = 0; i < 9; ++i) {
    ll x;
    cin >> x;
    oss << x;
  }
  stats = oss.str();
  visit.insert({stats, 0});

  cout << Bfs();

  return 0;
}