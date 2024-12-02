/*
This program needs to read in the input file. This input file contains two lists of numbers in a column-wise format where each number on each row is separated by a space and each row is separated by a newline. Once each list is read in, the length of each list should be validated to ensure that they are the same length. If they are not the same length, the program should print an error message and exit. If they are the same length, the program should then sort them from lowest value to highest, and calculate the sum of the differences of the two lists and print the result to the console.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// part 2
#include <unordered_map>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    // --- Part 1: Calculate the differences between two sorted lists ---
    std::vector<int> list1;
    std::vector<int> list2;
    int num1, num2;
    while (inputFile >> num1 >> num2) {
        list1.push_back(num1);
        list2.push_back(num2);
    }

    if (list1.size() != list2.size()) {
        std::cerr << "Error: Lists are not the same length" << std::endl;
        return 1;
    }

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    int sum = 0;
    for (int i = 0; i < list1.size(); i++) {
        sum += std::abs(list1[i] - list2[i]);
    }

    std::cout << "art 1 | Sum of differences: " << sum << std::endl;

    // --- Part 2: Calculate the similarity score between two sorted lists ---
    /*
    For each number in list1, find the number of times it occures in list2. Multiply
    the number of occurences in list2 by the value of the number in list1. Sum all of
    these values together and print the result to the console.
    */
    
    std::unordered_map<int, int> frequency;

    for(int num : list2) {
        frequency[num]++;
    }

    int similarityScore = 0;
    for (int num : list1) {
        similarityScore += num * frequency[num];
    }

    std::cout << "Part 2 | Similarity score: " << similarityScore << std::endl;

    return 0;  
}   // end of main