use std::fs::File;
use std::io::{self, BufRead};
use regex::Regex;

fn main(){
    // Recieve a command line argument and open the file
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        println!("Usage: {} <input file>", args[0]);
        return;
    }
    let file_name: &String = &args[1];
    println!("Opening file: {}", file_name);
    let file: File = File::open(file_name).unwrap();
    //let reader = io::BufReader::new(&file);
    //let line_count = io::BufReader::new(&file).lines().count();
    //println!("File contains {} lines of corrputed memory", line_count);

    let mut memory: Vec<String> = Vec::new();
    //for line in io::BufReader::new(&file).lines() {
    for line in io::BufReader::new(&file).lines() {
        let line = line.unwrap();
        // println!("Line: {}", line);
        memory.push(line);
    }
    println!("Memory fragments (lines): {:?}", memory.len());
    // go through and parse each memory fragment string getting the sum of all the products
    let mut sum: i32 = 0;
    for fragment in &memory {
        let products: Vec<i32> = parse_memory(fragment);
        sum += products.iter().sum::<i32>();
    }
    println!("Part 1 | Sum of products: {}", sum);
}

fn parse_memory(memory: &String) -> Vec<i32> {
    // Parse the memory string using regex to find expressions matching
    // the pattern: "mul\((\d{1,3}),(\d{1,3})\)" and extract the two
    // numbers.
    let mut products: Vec<i32> = Vec::new();
    let re = Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();
    for cap in re.captures_iter(memory) {
        let a = cap[1].parse::<i32>().unwrap();
        let b = cap[2].parse::<i32>().unwrap();
        products.push(a*b);
    }

    return products;
}