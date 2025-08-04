#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

// A more modern and readable implementation of the bottom-up merge sort algorithm.
// This version uses C++ streams for file I/O and avoids C-style macros.

// Function to merge two sorted sub-arrays.
void merge(std::vector<long long>::iterator begin,
           std::vector<long long>::iterator mid,
           std::vector<long long>::iterator end) {
  std::vector<long long> left_half(std::make_move_iterator(begin),
                                     std::make_move_iterator(mid));
  std::vector<long long> right_half(std::make_move_iterator(mid),
                                      std::make_move_iterator(end));

  std::merge(std::make_move_iterator(left_half.begin()),
             std::make_move_iterator(left_half.end()),
             std::make_move_iterator(right_half.begin()),
             std::make_move_iterator(right_half.end()), begin);
}

// Function to perform bottom-up merge sort.
void merge_sort(std::vector<long long>::iterator begin,
                std::vector<long long>::iterator end) {
  long long n = std::distance(begin, end);

  // The size of the sub-arrays to be merged.
  // It starts at 1 and doubles in each iteration.
  for (long long size = 1; size < n; size *= 2) {
    // Iterate over the array and merge sub-arrays of the current size.
    for (auto i = begin; i < end; i += 2 * size) {
      auto mid = std::min(i + size, end);
      auto current_end = std::min(i + 2 * size, end);
      merge(i, mid, current_end);
    }
  }
}

int main() {
  // Open the input and output files.
  std::ifstream input_file("input.txt");
  std::ofstream output_file("output.txt");

  if (!input_file.is_open() || !output_file.is_open()) {
    std::cerr << "Error opening files." << std::endl;
    return 1;
  }

  long long n{};
  input_file >> n;

  std::vector<long long> arr(n);
  for (long long i = 0; i < n; ++i) {
    input_file >> arr[i];
  }

  merge_sort(arr.begin(), arr.end());

  for (const auto &val : arr) {
    output_file << val << '\n';
  }

  return 0;
}