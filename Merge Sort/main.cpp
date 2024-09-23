#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <vector>

#define int long long
using vi = std::vector<int>;
using namespace std;
using vii = std::vector<int>::iterator;

void merge(vii a, vii a_end, vii b, vii b_end, vii temp_it) {
  vii a_copy{a}, a_end_copy{a_end}, b_copy{b}, b_end_copy{b_end},
      temp_it_copy{temp_it};
  while (a_copy < a_end_copy && b_copy < b_end_copy) {
    if (*a_copy < *b_copy) {
      *temp_it_copy = *a_copy;
      a_copy++;
    } else {
      *temp_it_copy = *b_copy;
      b_copy++;
    }
    temp_it_copy++;
  }

  while (a_copy < a_end_copy) {
    *temp_it_copy = *a_copy;
    a_copy++;
    temp_it_copy++;
  }
  while (b_copy < b_end_copy) {
    *temp_it_copy = *b_copy;
    b_copy++;
    temp_it_copy++;
  }
  vii a_copy_2{a}, b_end_copy_2{b_end}, temp_it_copy_2{temp_it};
  swap_ranges(a_copy_2, b_end_copy_2, temp_it_copy_2);
}

void merge_sort(vii start, vii end) {
  int n{std::distance(start, end)};
  vi temp{vi(n, 0)};

  for (int m{1}; m < n; m *= 2) {

    for (int i{}; i < n; i += 2 * m) {
      vii a{start + i};
      vii a_end{min(a + m, end)}; // end exclusive
      vii b{a_end};
      vii b_end{min(b + m, end)}; // end exclusive

      merge(a, a_end, b, b_end, temp.begin() + i);
    }
  }
}

signed main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n{};
  cin >> n;

  vi arr{vi(n, 0)};
  for (int i{}; i < n; ++i) {
    int arg{};
    cin >> arg;
    arr[i] = arg;
  }

  merge_sort(arr.begin(), arr.end());

  for (int i{}; i < n; ++i) {
    cout << arr[i] << '\n';
  }
  return 0;
}