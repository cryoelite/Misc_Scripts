# Merge Sort

This directory contains a C++ implementation of the bottom-up (iterative) Merge Sort algorithm.

## Algorithm

The traditional merge sort algorithm works by recursively dividing the array into smaller sub-arrays until each sub-array has only one element. Then, it merges the sub-arrays back together in a sorted order.

The bottom-up approach works as follows:
1.  It starts by merging sub-arrays of size 1 to create sorted sub-arrays of size 2.
2.  Then, it merges the sorted sub-arrays of size 2 to create sorted sub-arrays of size 4.
3.  This process continues until the entire array is sorted.

![merge sort from programiz](merge-sort-example_0.png)

## How to use

### Prerequisites
- A C++ compiler that supports C++20.

### Compilation
To compile the code, run the following command in the `Merge Sort` directory:
```bash
clang++ -std=c++20 main.cpp -o main
```

### Usage
The program reads a list of integers from `input.txt`, sorts them, and writes the sorted list to `output.txt`.

1.  Create an `input.txt` file in the `Merge Sort` directory.
2.  The first line of `input.txt` should be the number of integers `n`.
3.  The following `n` lines should contain the integers to be sorted.

#### Example `input.txt`
```
5
5
4
3
2
1
```

After running the program, `output.txt` will contain:
```
1
2
3
4
5
```
