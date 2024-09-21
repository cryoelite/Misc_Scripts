#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#define int long long
using vi = std::vector<int>;
using namespace std;

void merge(int a_start, int mid, int b_end, vi &arr, vi &temp, int temp_index) {
  int a{a_start}, b{mid}, j{temp_index};
  while (a < mid && b < b_end) {
    if (arr[a] < arr[b]) {
      temp[j] = arr[a];
      ++a;
    } else {
      temp[j] = arr[b];
      ++b;
    }
    ++j;
  }
  for (int i{a}; i < mid; ++i) {
    temp[j++] = arr[i];
  }
  for (int i{b}; i < b_end; ++i) {
    temp[j++] = arr[i];
  }

  for (int i{a_start}, j{temp_index}; i < b_end; ++i, ++j) {
    arr[i] = temp[j];
  }
}

void merge_sort(int start_index, int end_index, vi &arr, vi &temp) {
  // Assuming start_index<end_index and both < arr.size()
  int n{end_index - start_index + 1};

  // sorting for each value of m, which grows with the power of 2.
  for (int m{1}; m < n; m *= 2) {

    // make pairs, go from start to end, jump by 2m, 2m because m would be size
    // of first block, and then m would be size of second block, making it 2m
    
    for (int i{start_index}, temp_index{0}; i < end_index;
         i += 2 * m, temp_index += 2 * m) {
      int a_start{i};
      int mid{a_start + m};
      int b_end{min(mid + m, end_index + 1)};

      merge(a_start, mid, b_end, arr, temp, temp_index);
    }
  }

  swap_ranges(temp.begin(), temp.end(), arr.begin() + start_index);
}

signed main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n{};
  cin >> n;

  vi arr{vi(n, 0)};
  vi temp{vi(n, 0)};
  for (int i{}; i < n; ++i) {
    int arg{};
    cin >> arg;
    arr[i] = arg;
  }

  merge_sort(0, n - 1, arr, temp);

  return 0;
}