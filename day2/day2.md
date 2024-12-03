# Day 2

For day 2 we're tasked with analyzing "reports" coming out of reactor data. The puzzle input is lines of texts containing numbers separated by spaces. 

## Part 1

The goal is to figure out if the reports are "safe" or "unsafe." A report only counts as safe if both of the following are true:

1. The levels are either all increasing or all decreasing.
2. Any two adjacent levels differ by at least one and at most three.

For this part we will need to parse the input. I'll start by reading each line and splitting it into a list of integers validating that each line has at least two numbers and contains only numbers. Once we have the data safely into an appropriate container, we can traverse the list and check if the levels are increasing or decreasing and if the difference between adjacent levels is within the specified range.