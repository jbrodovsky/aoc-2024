use std::fs::File;
use std::io::{self, BufRead};

#[derive(Debug, Clone, Copy)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight,
}

impl Direction {
    fn to_offset(&self) -> (i32, i32) {
        match self {
            Direction::Up => (0, -1),
            Direction::Down => (0, 1),
            Direction::Left => (-1, 0),
            Direction::Right => (1, 0),
            Direction::UpLeft => (-1, -1),
            Direction::UpRight => (1, -1),
            Direction::DownLeft => (-1, 1),
            Direction::DownRight => (1, 1),
        }
    }
}

fn main() {
    // Recieve command line arguments for the input file and word to search for
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 3 {
        println!("Usage: {} <input file> <word>", args[0]);
        return;
    }
    // Read in the text file and create a 2D array of characters
    let file_name: &String = &args[1];
    println!("Opening file: {}", file_name);
    let grid: Vec<Vec<char>> = read_grid(file_name);
    // Validate that the grid has been read in correctly by printing the size and the grid
    println!("Grid size: {}x{}", grid.len(), grid[0].len());    
    // Perform word search on the grid
    let word: &String = &args[2];
    let count: i32 = word_search(&grid, word);
    println!("Part 1 | XMAS word count: {}", count);
    let xmas_count: i32 = x_word_search(&grid);
    println!("Part 2 | X-MAS word count: {}", xmas_count);
}

fn read_grid(file_name: &String) -> Vec<Vec<char>> {
    // Read in the text file and create a 2D array of characters
    let file: File = File::open(file_name).unwrap();
    let mut grid: Vec<Vec<char>> = Vec::new();
    for line in io::BufReader::new(&file).lines() {
        let line: String = line.unwrap();
        let mut row: Vec<char> = Vec::new();
        for c in line.chars() {
            row.push(c);
        }
        grid.push(row);
    }
    return grid;
}

fn word_search(grid: &Vec<Vec<char>>, word: &String) -> i32 {
    // Perform word search on the grid
    let mut count: i32 = 0;
    for row in 0..grid.len() {
        for col in 0..grid[row].len() {
            if grid[row][col] == word.chars().nth(0).unwrap() {
                for dir in &[
                    Direction::Up,
                    Direction::Down,
                    Direction::Left,
                    Direction::Right,
                    Direction::UpLeft,
                    Direction::UpRight,
                    Direction::DownLeft,
                    Direction::DownRight,
                ] {
                    if search(grid, word, row as i32, col as i32, dir) {
                        count += 1;
                    }
                }
                
            }
        }
    }
    return count;
}

fn search(grid: &Vec<Vec<char>>, word: &String, row: i32, col: i32, dir: &Direction) -> bool {
    // Search for the word in the grid in the given direction
    let (dx, dy) = dir.to_offset();
    let mut r: i32 = row;
    let mut c: i32 = col;
    for i in 0..word.len() {
        if r < 0 || r >= grid.len() as i32 || c < 0 || c >= grid[0].len() as i32 {
            return false; // Out of bounds
        }
        if grid[r as usize][c as usize] != word.chars().nth(i).unwrap() {
            return false; // Mismatch
        }
        // else, increment
        r += dy;
        c += dx;
    }
    // success!
    return true;
}

fn x_word_search(grid: &Vec<Vec<char>>) -> i32 {
    // Perform word search on the grid trying to find "MAS" in a x-shaped pattern in the grid
    let mut count: i32 = 0;
    for row in 0..grid.len() {
        for col in 0..grid[row].len() {
            if grid[row][col] == 'A' && row >= 1 && col >= 1 && row < grid.len()-1 && col < grid[row].len()-1 { // insures that the "A" is not on the edge of the grid          
                let upper_left: char = grid[row-1][col-1];
                let upper_right: char = grid[row-1][col+1];
                let lower_left: char = grid[row+1][col-1];
                let lower_right: char = grid[row+1][col+1];

                // create a string from the upper left to lower right
                let mut diag1: String = String::new();
                diag1.push(upper_left);
                diag1.push(grid[row][col]);
                diag1.push(lower_right);
                // create a string from the upper right to lower left
                let mut diag2: String = String::new();
                diag2.push(upper_right);
                diag2.push(grid[row][col]);
                diag2.push(lower_left);
                // check if the diagonals contain "MAS" or "SAM"
                if (diag1 == "MAS" || diag1 == "SAM") && (diag2 == "MAS" || diag2 == "SAM") {
                    count += 1;
                }
            }
        }
    }
    return count;
}