# Day 1 - Historian Histaria

[Original puzzle post here](https://adventofcode.com/2024/day/1)

## Problem 1

The main part of the problem appears to be this:

> ...pair up the numbers and measure how far apart they are. Pair up the smallest number in the left list with the smallest number in the right list, then the second-smallest left number with the second-smallest right number, and so on.
> Within each pair, figure out how far apart the two numbers are; you'll need to add up all of those distances. For example, if you pair up a 3 from the left list with a 7 from the right list, the distance apart is 4; if you pair up a 9 with a 3, the distance apart is 6.
>To find the total distance between the left list and the right list, add up the distances between all of the pairs you found. In the example above, this is 2 + 1 + 0 + 1 + 2 + 5, a total distance of 11!

This seems like a pretty straightforward problem. Given an input of two lists of numbers, validate that they are the same length, sort them, and then calculate the distance between each pair of numbers. Finally, sum all of the distances and return the result.

Using NumPy or some other similar linear algebra library would make this pretty easy:

```python
import numpy as np

# read left array
left = np.array([int(x) for x in input().split()])
# read right array
right = np.array([int(x) for x in input().split()])

left = np.sort(left)
right = np.sort(right)

print(np.sum(np.abs(left - right)))
```
