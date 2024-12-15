#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <array>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

constexpr std::pair<int, int> direction_to_offset(Direction dir){
    switch (dir) {
        case Direction::UP: return {-1, 0};
        case Direction::DOWN: return {1, 0};
        case Direction::LEFT: return {0, -1};
        case Direction::RIGHT: return {0, 1};
        case Direction::UP_LEFT: return {-1, -1};
        case Direction::UP_RIGHT: return {-1, 1};
        case Direction::DOWN_LEFT: return {1, -1};
        case Direction::DOWN_RIGHT: return {1, 1};
        default: return {0, 0};
    }
}

std::vector<std::vector<char>> read_grid(std::ifstream& inputFile) {
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    return grid;
}

bool search(const std::vector<std::vector<char>>& grid, const std::string& word, int row, int col, Direction dir) {
    // Search for the word in the grid starting at the given row and column
    // and moving in the given direction
    std::pair<int, int> offset = direction_to_offset(dir);
    
    for (char c : word) {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
            return false; // Out of bounds
        }
        if (grid[row][col] != c) {
            return false; // Mismatch
        }
        // else increment
        row += offset.first;
        col += offset.second;
    }
    return true;
}

int word_search(const std::vector<std::vector<char>>& grid, const std::string& word) {
    // Search for the word in the grid and return the number of times it appears
    constexpr std::array<Direction, 8> directions = {
        Direction::UP,
        Direction::DOWN,
        Direction::LEFT,
        Direction::RIGHT,
        Direction::UP_LEFT,
        Direction::UP_RIGHT,
        Direction::DOWN_LEFT,
        Direction::DOWN_RIGHT
    };
    int count = 0;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            for (Direction dir : directions) {
                if (search(grid, word, row, col, dir)) {
                    ++count;
                }
            }
        }
    }
    return count;
}

int x_mas_count(const std::vector<std::vector<char>>& grid){
    int count = 0;
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == 'A' && r >= 1 && c >=1 && r < grid.size() - 1 && c < grid[0].size() - 1) {
                char upper_left = grid[r-1][c-1];
                char upper_right = grid[r-1][c+1];
                char lower_left = grid[r+1][c-1];
                char lower_right = grid[r+1][c+1];

                std::string diag1;
                diag1.push_back(upper_left);
                diag1.push_back(grid[r][c]);
                diag1.push_back(lower_right);

                std::string diag2;
                diag2.push_back(upper_right);
                diag2.push_back(grid[r][c]);
                diag2.push_back(lower_left);

                if ((diag1 == "MAS" || diag1 == "SAM") && (diag2 == "MAS" || diag2 == "SAM")) {
                    ++count;
                }
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]){
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <word>" << std::endl;
        return 1;
    }
    std::cout << "Opening file: " << argv[1] << std::endl;
    // Read in the text file and create a 2D array of characters using function read_grid()
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    std::vector<std::vector<char>> grid = read_grid(inputFile);
    // Search for the word in the grid and print the number of times it appears
    std::string word = argv[2];
    int count = word_search(grid, word);
    std::cout << "Part 1 | " << word << " appears " << count << " times in the grid" << std::endl;
    count = x_mas_count(grid);
    std::cout << "Part 2 | X-MAS appears " << count << " times in the grid" << std::endl;

    return 0;
}