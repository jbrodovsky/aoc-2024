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
        let line: String = line.unwrap();
        // println!("Line: {}", line);
        memory.push(line);
    }
    println!("Memory fragments (lines): {:?}", memory.len());
    
    // Part 1: go through and parse each memory fragment string getting the sum of all the products
    let mut sum: i32 = 0;
    let re: Regex = Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();
    for fragment in &memory {
        let products: Vec<i32> = parse_memory(fragment, &re);
        sum += products.iter().sum::<i32>();
    }
    println!("Part 1 | Sum of products: {}", sum);
    // Part 2
    let full_memory: String = std::fs::read_to_string(file_name).unwrap();
    let re: Regex = Regex::new(r"do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\)").unwrap();
    let products: Vec<i32> = parse_memory_part2(&full_memory, &re);
    let sum: i32 = products.iter().sum::<i32>();

    println!("Part 2 | Sum of products: {}", sum);

}

fn parse_memory(memory: &String, re: &Regex) -> Vec<i32> {
    // Parse the memory stringmul\((\d{1,3}),(\d{1,3})\) using regex to find expressions matching
    // the pattern: "mul\((\d{1,3}),(\d{1,3})\)" and extract the two
    // numbers.
    let mut products: Vec<i32> = Vec::new();
    for cap in re.captures_iter(memory) {
        let a: i32 = cap[1].parse::<i32>().unwrap();
        let b: i32 = cap[2].parse::<i32>().unwrap();
        products.push(a*b);
    }

    return products;
}

fn parse_memory_part2(memory: &String, re: &Regex) -> Vec<i32> {
    let mut products: Vec<i32> = Vec::new();
    let mut process_mul: bool = true;

    for cap in re.captures_iter(memory) {
        let match_str: &str = cap.get(0).unwrap().as_str();
        //print!("Match: {}\t", match_str);
        if match_str == "do()" {
            process_mul = true;
            //print!("Enabling! ");
        }
        else if match_str == "don't()" {
            //print!("Disabling! ");
            process_mul = false;
        }
        //let re = Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();
        else if process_mul {            
            // Process `mul` commands if toggled on
            // Extract the numbers from the first matching group
            let a: i32 = cap[1].parse::<i32>().unwrap();
            let b: i32 = cap[2].parse::<i32>().unwrap();
            //print!("Adding product: {}*{}={} ", a, b, a*b);
            products.push(a*b);
        }
        //println!();
    }
    return products;
}