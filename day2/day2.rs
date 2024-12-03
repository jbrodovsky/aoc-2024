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

fn calculate_differences(report: &Vec<i32>) -> Vec<i32> {
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
    if !(all_positive(&differences) || all_negative(&differences)) {
        return false;
    }
    for diff in differences {
        if diff.abs() > 3 || diff.abs() < 1 {
            return false;
        }
    }
    return true;
}

/*
The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate a single bad level in what would otherwise be a safe report. It's like the bad level never happened!

Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.
*/

fn check_levels_damped(report: &Vec<i32>) -> bool {
    for i in 0..report.len() {
        let mut damped = report.clone();
        damped.remove(i);
        if check_levels(&calculate_differences(&damped)) {
            return true;
        }
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
    for report in &reports {
        let differences = calculate_differences(&report);
        if check_levels(&differences) {
            //println!("Report: {:?} | {:?} is SAFE", report, differences);
            safe_reports += 1;
        }
    }
    println!("Part 1 | Number of safe reports: {}", safe_reports);
    // Part 2
    safe_reports = 0;
    for report in &reports {
        let differences = calculate_differences(&report);
        if check_levels(&differences) {
            //println!("Report: {:?} | {:?} is SAFE", report, differences);
            safe_reports += 1;
        }
        else if check_levels_damped(&report) {
            //println!("Report: {:?} | {:?} is SAFE", report, differences);
            safe_reports += 1;
        }
        else {
            //println!("Report: {:?} | {:?} is UNSAFE", report, differences);
            //println!("... UNSAFE")
        }
    }
    println!("Part 2 | Number of safe reports when damped: {}", safe_reports);
}