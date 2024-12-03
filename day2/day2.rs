use std::fs::File;
use std::io::{self, BufRead};

// Recieve a line of the input file and transform it into a Vec<i32>
fn parse_line(line: String) -> Vec<i32> {
    //let line = line.unwrap();
    let numbers: Vec<i32> = line
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();
    return numbers;
}

fn calculate_difference(report: &Vec<i32>) -> Vec<i32> {
    let mut differences: Vec<i32> = Vec::new();
    for i in 1..report.len() {
        differences.push(report[i] - report[i-1]);
    }
    return differences;
}

fn all_positive(differences: &Vec<i32>) -> bool {
    for diff in differences {
        if *diff < 0 {
            return false;
        }
    }
    return true;
}
fn all_negative(differences: &Vec<i32>) -> bool {
    for diff in differences {
        if *diff > 0 {
            return false;
        }
    }
    return true;
}
fn check_levels(differences: &Vec<i32>) -> bool {
    if all_positive(&differences) || all_negative(&differences) {
        for diff in differences {
            if diff.abs() > 3 || diff.abs() < 1 {
                return false;
            }
        }
        return true;
    }
    return false;
}

fn main(){
    // Recieve a command line argument for the input file
    let args: Vec<String> = std::env::args().collect();

    if args.len() != 2 {
        println!("Usage: {} <input file>", args[0]);
        return;
    }
    let file_name = &args[1];
    // iterate through the lines of the file
    let file = File::open(file_name).unwrap();
    let mut reports: Vec<Vec<i32>> = Vec::new();

    for line in io::BufReader::new(file).lines() {
        let line = line.unwrap();
        reports.push(parse_line(line));
    }
    // print the number of reports
    println!("Number of reports: {}", reports.len());
    let mut safe_reports = 0;
    for report in reports {
        let differences = calculate_difference(&report);
        if check_levels(&differences) {
            //println!("Report: {:?} | {:?} is SAFE", report, differences);
            safe_reports += 1;
        }
        else {
            println!("Report: {:?} | {:?} is UNSAFE", report, differences);
        }
    }

    println!("Number of safe reports: {}", safe_reports);
}