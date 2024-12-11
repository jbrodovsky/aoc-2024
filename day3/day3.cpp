#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <regex>


std::vector<int> parseMemory(const std::string& fragment, std::regex re) {
    // Parse the memory string using regex to find expressions matching
    // the pattern: "mul\((\d{1,3}),(\d{1,3})\)" and extract the two
    // numbers.
    bool process_mul = true;

    std::vector<int> products;
    std::sregex_iterator begin(fragment.begin(), fragment.end(), re);
    std::sregex_iterator end;
    int a = 0;
    int b = 0;
    for (auto it = begin; it != end; ++it) {
        std::string match_str = (*it).str();
        //std::cout << "Match: " << match_str << " | ";
        if (match_str == "do()") {
            process_mul = true;
            //std::cout << "Enabling"; // << std::endl;
        } else if (match_str == "don't()") {
            process_mul = false;
            //std::cout << "Disabling"; // << std::endl;
        } else if (process_mul) {
            a = std::stoi((*it)[1].str());
            b = std::stoi((*it)[2].str());
            //std::cout << "Adding product: " << a << "*" << b << "=" << a*b;
            products.push_back(a * b);
        }
        //std::cout << std::endl;  
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
    // Read the entire file into a string
    std::ostringstream buffer;
    buffer << inputFile.rdbuf();
    std::string memory = buffer.str();
    //std::cout << "Memory: " << memory << std::endl;
    
    // --- Part 1 -----
    // Read each line in the input file and add it to a list of strings
    std::regex re(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::vector<int> products = parseMemory(memory, re);
    std::cout << "Part 1 | Sum of all products: " << std::accumulate(products.begin(), products.end(), 0) << std::endl;

    // --- Part 2 -----
    std::regex re2(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
    products = parseMemory(memory, re2);
    std::cout << "Part 2 | Sum of all products: " << std::accumulate(products.begin(), products.end(), 0) << std::endl;

}
