# Algorithm
```cpp
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
```
And then we merge with simply ``merge_sort(<begin iterator>, <end iterator (exclusive)>);``.

- The logic is simple, we go bottom-up merge sort. Traditional merge sort works like so
1. Divide the array of size n into n/2 sized blocks, then divide the n/2 blocks into n/4 sized blocks and keep dividing till we get 1 sized blocks. If the block can't be made of a particular size, then we clamp the size into the size it can fit into. For ex.: if we have to make n/2 sized blocks and there are 5 elements, then first block will get 3 elements, the next only 2.
2. Start merging the blocks, from 1 sized blocks all the way up till n/2 sized blocks. Sort the blocks as we merge.
3. Voila!

![merge sort from programiz](merge-sort-example_0.png)

- The sorting is pretty simple, if we have 2 blocks, say 1 has elements [2,5,9] and the other has [1,10], we put 2 pointers at the beginning of both blocks and compare the elements and merge into an array comparing the pointed elements, when a pointer's value is taken it moves ahead, so our 3 arrays in this case are, [], [10] and [1,2,5,9]. Now, we will always be left with at most 1 array with its contents, by our logic all the elements in the merged array are smaller than the rest of the remaining array, so we simply append its elements at the back of the merged array. Now how did we get sorted [2,5,9] and [1,10] in the first place ? It's because we sort bottom-up, meaning when we had 1 sized blocks, we compared them, we might have had [5] and [2] and it gave us [2,5] and so on.

- The logic for bottom-up iterative sort works similarly, but we don't go breaking down n/2 and so on, but instead start at 1 sized blocks, hence the bottom up. It is pretty straight forward

1. First, We have ``m`` which is the current block size, it goes from 1 to n, n is the size of the array or the piece of the array we have to sort. ``m`` goes up by powers of 2 but the size of m shouldn't exceed ``n``, because if it does, then we wouldn't be able to get proper blocks, we need 2 blocks per sub-iteration, and atleast 2 total blocks. So if ``n`` is 8 and ``m`` becomes 8, then we would only have 1 block and 1 sub-block. A sub-block is a block in the lower iteration (the ``i`` loop).

2. Next for each m sized block we go from first index in the range to last index (exclusive) and make jumps of `2` blocks, because in each iteration (sub-iteration from the perspective of above loop), we have 2 blocks, a and b. a starts at `i`, and ends at `i+m`, so if `i` is `0` and `m` is `1`, then we get a with index 0 only, then b starts at either `i+m` or at end index, this is because say `i+m` is the end of the range, say `n` is `3` and `i` is `2` then `2 + 1` will take us out of the array, we clamp it and get `2` in `a_end` as well as in `b_end`. Since ends are exclusive and our `merge` function would later not traverse `end` to `end` (`end` is not less than `end`), it means we would only have 1 block and it will simply by appended at the end.  
The jump of `i+=2*m` works because 2 blocks are included in a single iteration, and the end element is then used by the next iteration, i.e., say `m` is `1` and `i` is `0` then we get `i+=2*1` which makes `i` become `2`, our previous iteration only got the values from `0` to `1`, then `1` to `2`, ends were exclusive so `2` was actually left, now it will be included.

3. The `merge` function is pretty simple, compare the arrays by using 2 pointers and sort them, then append the remainder array and finally swap the temporary and the main array.

5. And our array is sorted!
   
Q. But what happens to the elements that are appended at the back because they had a single block ?
A. They are sorted in and brought in as well, this is ensured by our first condition, when `m` is less than n, say n is 8 then m will be at max only 4. So if say n is 5, when m will be 2 then indices will be paired like so [0] and [1], [2] and [3], [4] where the fifth element isn't sorted to anything at all, but then m will be 4, and the pairs will be [0,1,2,3] and [4], now it will be sorted into the final array.
