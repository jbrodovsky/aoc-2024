#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <regex>


std::vector<int> parseMemory(const std::string& fragment) {
    // Parse the memory string using regex to find expressions matching
    // the pattern: "mul\((\d{1,3}),(\d{1,3})\)" and extract the two
    // numbers.
    std::vector<int> products;
    std::regex re(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::sregex_iterator begin(fragment.begin(), fragment.end(), re);
    std::sregex_iterator end;

    for (auto it = begin; it != end; ++it) {
        int a = std::stoi(it->str(1));
        int b = std::stoi(it->str(2));
        products.push_back(a * b);
    }
    return products;
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    std::cout << "Opening file: " << argv[1] << std::endl;
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    std::vector<std::string> memory;
    std::string line;
    while (std::getline(inputFile, line)) {
        memory.push_back(line);
    }
    // --- Part 1 -----
    // Read each line in the input file and add it to a list of strings
    int sum = 0;
    for (const std::string& fragment : memory) {
        std::vector<int> products = parseMemory(fragment);
        sum += std::accumulate(products.begin(), products.end(), 0);
    }
    std::cout << "Part 1 | Sum of all products: " << sum << std::endl;
}
