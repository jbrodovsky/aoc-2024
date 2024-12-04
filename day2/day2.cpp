/*
For this part we will need to parse the input. I'll start by reading each line and splitting it into a list of integers validating that each line has at least two numbers and contains only numbers. Once we have the data safely into an appropriate container, we can traverse the list and check if the levels are increasing or decreasing and if the difference between adjacent levels is within the specified range.
*/
#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> readLine(const std::string& line) {
    std::vector<int> result;
    std::string num;
    for (char c : line) {
        if (c == ' ') {
            result.push_back(std::stoi(num));
            num.clear();
        } else {
            num += c;
        }
    }
    if (!num.empty()) {
        result.push_back(std::stoi(num));
    }
    return result;
}

std::vector<int> calculateDifferences(const std::vector<int>& levels) {
    std::vector<int> differences;
    for (int i = 1; i < levels.size(); i++) {
        differences.push_back(levels[i] - levels[i - 1]);
    }
    return differences;
}

bool allPositive(const std::vector<int>& differences) {
    for (int diff : differences) {
        if (diff < 0) {
            return false;
        }
    }
    return true;
}

bool allNegative(const std::vector<int>& differences) {
    for (int diff : differences) {
        if (diff > 0) {
            return false;
        }
    }
    return true;
}


bool checkLevels(const std::vector<int>& differences){
    if (!(allPositive(differences) || allNegative(differences))) {
        return false;
    }
    // Check to see if the magnitude of the differences is within the specified range of >= 1 and <= 3
    for (int diff : differences) {
        if (std::abs(diff) < 1 || std::abs(diff) > 3) {
            return false;
        }
    }
    return true;
}

/*
The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate a single bad level in what would otherwise be a safe report. It's like the bad level never happened!

Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.
*/

bool checkLevelsDamped(const std::vector<int>& report){
    for (int i = 0; i < report.size(); i++) {
        std::vector<int> damped(report);
        damped.erase(damped.begin() + i);
        if (checkLevels(calculateDifferences(damped))) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    // --- Part 1 -----
    // read each line in the input file and split it into a list of integers
    std::vector<std::vector<int>> reports;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<int> report = readLine(line);
        if (report.size() < 2) {
            std::cerr << "Error: Each line must contain at least two numbers" << std::endl;
            return 1;
        }
        reports.push_back(report);
    }

    std::cout << "Read in " << reports.size() << " reports" << std::endl;

    int safeReports = 0;

    for (const std::vector<int>& report : reports) {
        std::vector<int> differences = calculateDifferences(report);
        if (checkLevels(differences)) {
            safeReports++;
        }
     }

    std::cout << "Part 1 | Number of safe reports: " << safeReports << std::endl;

    // --- Part 2 -----
    safeReports = 0;
    for (const std::vector<int>& report : reports) {
        std::vector<int> differences = calculateDifferences(report);
        if (checkLevels(differences)) {
            safeReports++;
        }
        else if (checkLevelsDamped(report)) {
            safeReports++;
        }
    }

    std::cout << "Part 2 | Number of safe reports when damped: " << safeReports << std::endl;
}