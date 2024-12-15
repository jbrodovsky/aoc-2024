# Day 5

This puzzle poses a problem of printing updates to a safety manual. There is a set of rules as to which pages should be printed before other pages formated as `A|B` where `A` should be printed before `B`. There is also a list of updates which in turn has a list of updated pages to be printed. The first task is to determin which updates are in the correct order. The second task is to determine the sum of the middle number in all the correctly sorted updates.

## Part 1

The first task is to determine the correct order of the updates. This can be done by creating a directed graph where each node is an update and each edge is a rule. The graph can then be traversed in topological order to determine the correct order of the updates.

```python
from collections import defaultdict
from typing import List, Tuple

def parse_input(input_string: str) -> Tuple[defaultdict, List[str]]:
    rules = defaultdict(list)
    updates = []
    for line in input_string.split("\n"):
        if not line:
            continue
        if "|" in line:
            a, b = line.split("|")
            rules[b.strip()].append(a.strip())
        else:
            updates.append(line.strip())
    return rules, updates

def topological_sort(rules: defaultdict, updates: List[str]) -> List[str]:
    visited = set()
    stack = []
    def dfs(node):
        visited.add(node)
        for child in rules[node]:
            if child not in visited:
                dfs(child)
        stack.append(node)
    for node in updates:
        if node not in visited:
            dfs(node)
    return stack[::-1]
```

