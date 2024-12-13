# Day 4

For this day's puzzle, we are tasked with completing a word serach puzzle. We need to find all instances of `XMAS` in a word search grid. The four characters can be vertical, horizontal, or diagonal and can be forwards or reversed.

This seems like a pretty straightforward regex problem again, but the diagonals are going to be a bit tricky. As it turns out, there is a standardized word search algorithm. This algorithm searches the entire grid for the first letter in the target word. If it finds it, it then checks along all 8 directions iteratively for the length of the word to see if the letter at that grid location matches the `i`th letter in the target word. If successfully iterated through, the word is found and a true value is returned.
