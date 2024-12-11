# Day 3

Today's problem poses a string parseing problem as part of "memory corruption" problem. The program is trying to execute multiplication commands of the format `mul(a,b)` where `a` and `b` are integers of 1-3 digits. Commands formatted like `mul(a,` `mul ( a, b)` et cetera should be ignored. The goal is to scan the "memory" string and find all the valid `mul` commands and calculate the sum of all these products.

The problem is solved by using regular expressions to find all the valid `mul` commands and then calculating the sum of all the products. The code is as follows:

```python
import re

def find_mul_commands(memory):
    mul_commands = re.findall(r'mul\((\d{1,3}),(\d{1,3})\)', memory)
    return mul_commands

def calculate_sum_of_products(memory):
    mul_commands = find_mul_commands(memory)
    sum_of_products = 0
    for a, b in mul_commands:
        sum_of_products += int(a) * int(b)
    return sum_of_products

memory = "mul(2,3) mul(4,5) mul(6,7)"
print(calculate_sum_of_products(memory)) # Output: 44
```

So this problem is going to be a bit more difficult to solve in Rust as the Rust standard library does not support regular expressions. That said, one of the maintainers of the [`regex`](https://crates.io/crates/regex) crate is the [Rust language maintainers](https://github.com/rust-lang) soooo... I'm considering this fair game.

Part two of this problem introdues a new command: `do()` and `don't()` which act as a "toggle" for the `mul` command. If `do()` is called, the following `mul` commands are executed, if `don't()` is called, the `mul` commands are ignored. Again, the goal is to calculate the sum of all the products of the `mul` commands that are executed. 
