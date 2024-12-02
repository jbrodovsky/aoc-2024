/*
This program needs to read in the input file. This input file contains two lists of numbers in a column-wise format where each number on each row is separated by a space and each row is separated by a newline. Once each list is read in, the length of each list should be validated to ensure that they are the same length. If they are not the same length, the program should print an error message and exit. If they are the same length, the program should then sort them from lowest value to highest, and calculate the sum of the differences of the two lists and print the result to the console.
*/

use std::fs::File;
use std::io::{self, BufRead};
use std::collections::HashMap;

fn main() {
    // Recieve a command line argument for the input file
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        println!("Usage: {} <input file>", args[0]);
        return;
    }
    // Get the file name from the command line arguments
    let file_name = &args[1];
    // Open the file in read-only mode
    let file = File::open(file_name).unwrap();
    let mut list1: Vec<i32> = Vec::new();
    let mut list2: Vec<i32> = Vec::new();

    // Read the file line by line using the lines() iterator from std::io::BufRead.
    for line in io::BufReader::new(file).lines() {
        let line = line.unwrap();
        let numbers: Vec<i32> = line
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        list1.push(numbers[0]);
        list2.push(numbers[1]);
    }

    // Validate the length of the two lists
    if list1.len() != list2.len() {
        println!("Error: The two lists are not the same length.");
        return;
    }

    // Sort the two lists
    list1.sort();
    list2.sort();

    // Calculate the sum of the differences of the two lists
    let mut sum_diff = 0;
    for i in 0..list1.len() {
        sum_diff += (list1[i] - list2[i]).abs();
    }

    // Print the result
    println!("Sum of differences: {}", sum_diff);

        // --- Part 2: Calculate the similarity score between two sorted lists ---
    /*
    For each number in list1, find the number of times it occures in list2. Multiply
    the number of occurences in list2 by the value of the number in list1. Sum all of
    these values together and print the result to the console.
    */

    let mut count_map = HashMap::new();
    for &num in &list2 {
        *count_map.entry(num).or_insert(0) += 1;
    }
    let mut similarity_score = 0;
    for &num in &list1 {
        if let Some(&count) = count_map.get(&num) {
            similarity_score += num * count;
        }
    }
    println!("Similarity score: {}", similarity_score);
}