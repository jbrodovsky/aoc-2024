#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <ranges>
#include <algorithm>
#include <stdexcept>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;
using InDegree = std::unordered_map<std::string, int>;

void parseRules(const std::string& rules, Graph& graph, InDegree& inDegree) {
    std::ifstream inputFile(rules);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file: " + rules);
    } 
    std::string line;
    while (std::getline(inputFile, line)) {
        auto delimiter = line.find('|');
        if (delimiter == std::string::npos) {
            std::cerr << "Invalid rule: " << line << std::endl;
            continue;
        }
        std::string before = line.substr(0, delimiter);
        std::string after = line.substr(delimiter + 1);
        
        // Trim whitespace using C++20 ranges
        auto trim = [](std::string& s) {
            s.erase(s.begin(), std::ranges::find_if(s, [](unsigned char ch) { return !std::isspace(ch); }));
            s.erase(std::ranges::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
        };
        trim(before);
        trim(after);
        
        // Update the graph based on the rule
        graph[before].push_back(after);
        inDegree[after]++;
        inDegree.try_emplace(before, 0);
    }
}

std::vector<std::string> topologicalSort(const Graph& graph, InDegree& inDegree) {
    auto localInDegree = inDegree;
    std::queue<std::string> zeroInDegreeQueue;
    std::vector<std::string> sortedOrder;
    // collect all nodes with zero in-degree
    for (const auto& [node, degree] : localInDegree | std::views::filter([](const auto& pair) { return pair.second == 0; })) {
        zeroInDegreeQueue.push(node);
    }
    // Process nodes in topological order
    while (!zeroInDegreeQueue.empty()) {
        std::string node = zeroInDegreeQueue.front();
        zeroInDegreeQueue.pop();
        sortedOrder.push_back(node);
        for (const std::string& neighbor : graph.at(node)) {
            localInDegree[neighbor]--;
            if (localInDegree[neighbor] == 0) {
                zeroInDegreeQueue.push(neighbor);
            }
        }
    }
    // Verify if topological sort was successful
    if (sortedOrder.size() != graph.size()) {
        throw std::runtime_error("Graph has a cycle!");
    }
    return sortedOrder;
}

std::string printGraph(std::unordered_map<std::string, std::vector<std::string>>& graph) {
    std::string result;
    for (const auto& node : graph) {
        result += node.first + " -> ";
        for (const auto& neighbor : node.second) {
            result += neighbor + " ";
        }
        result += "\n";
    }
    return result;
}

int main() {
   Graph graph;
    InDegree inDegree;
    const std::string rules = "rules.txt";
    parseRules(rules, graph, inDegree);
    std::cout << "Created graph with " << graph.size() << " nodes" << std::endl;
    std::cout << "Graph representation:" << std::endl;
    std::cout << printGraph(graph) << std::endl;

    std::vector<std::string> sortedOrder;
    try {
        sortedOrder = topologicalSort(graph, inDegree);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    std::cout << "Found a sorted solution!" << std::endl;
    for (const auto& node : sortedOrder) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}