#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <stdexcept>

using Graph = std::unordered_map<int, std::unordered_set<int>>;
using InDegree = std::unordered_map<int, int>;
using Rule = std::unordered_map<int, std::unordered_set<int>>;

// Function to parse rules from a file
Rule parseRules(const std::string& rulesFile) {
    std::ifstream inputFile(rulesFile);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file: " + rulesFile);
    }

    std::string line;
    Rule rules = {};
    while (std::getline(inputFile, line)) {
        auto delimiter = line.find('|');
        if (delimiter == std::string::npos) {
            std::cerr << "Invalid rule: " << line << std::endl;
            continue;
        }

        int from = std::stoi(line.substr(0, delimiter));
        int to = std::stoi(line.substr(delimiter + 1));

        // Add the rule
        if (rules[from].insert(to).second) {
            std::cout << "Added rule: " << printRule({from, to}) << std::endl;
        } else {
            std::cerr << "Duplicate rule ignored: " << printRule({from, to}) << std::endl;
        }        
    }
    return rules;
}

// Print the rules
void printRules(const Rule& rules) {
    std::cout << "Rules:\n";
    for (const auto& [from, to] : rules) {
        for (int rule : to) {
            std::cout << "  " << printRule({from, rule}) << "\n";
        }
    }
}

// Function to parse updates from a file
std::vector<std::vector<int>> parseUpdates(const std::string& updatesFile) {
    std::ifstream inputFile(updatesFile);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file: " + updatesFile);
    }

    std::string line;
    std::vector<std::vector<int>> updates;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<int> update;
        while (std::getline(ss, value, ',')) {
            update.push_back(std::stoi(value));
        }
        updates.push_back(update);
    }

    return updates;
}

std::string printRule(const Rule& rule) {
    return std::to_string(rule.first) + " -> " + std::to_string(rule.second);
}

void buildGraph(const std::vector<Rule>& rules, Graph& graph, InDegree& inDegree) {
    for (const auto& rule : rules) {
        int from = rule.first;
        int to = rule.second;

        // Ensure nodes exist in graph and inDegree
        graph[from];
        graph[to];
        inDegree[from];
        inDegree[to];

        // Add the edge
        if (graph[from].insert(to).second) {
            inDegree[to]++;
        } else {
            std::cerr << "Duplicate edge ignored: " << from << " -> " << to << std::endl;
        }
    }

    // Log the constructed graph and in-degree
    std::cout << "Graph Structure:\n";
    for (const auto& [node, neighbors] : graph) {
        std::cout << "  " << node << ": ";
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }

    std::cout << "In-Degree Map:\n";
    for (const auto& [node, degree] : inDegree) {
        std::cout << "  " << node << ": " << degree << "\n";
    }
}

std::vector<int> topologicalSort(const Graph& graph, InDegree inDegree) {
    std::queue<int> q;
    std::vector<int> sortedOrder;

    // Push all nodes with in-degree of 0 into the queue
    for (const auto& [node, degree] : inDegree) {
        if (degree == 0) {
            q.push(node);
        }
    }

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        sortedOrder.push_back(current);

        // Decrease the in-degree of neighbors
        for (const int neighbor : graph.at(current)) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Check for cycles
    if (sortedOrder.size() != graph.size()) {
        std::cerr << "Cycle detected in graph. Unable to perform topological sort.\n";
        throw std::runtime_error("Graph has a cycle, topological sort not possible.");
    }

    return sortedOrder;
}

bool validateUpdates(const std::vector<int>& sortedOrder, const std::vector<int>& updates) {
    std::unordered_map<int, int> positionMap;
    for (size_t i = 0; i < sortedOrder.size(); ++i) {
        positionMap[sortedOrder[i]] = i;
    }

    for (size_t i = 1; i < updates.size(); ++i) {
        if (positionMap[updates[i - 1]] > positionMap[updates[i]]) {
            return false;
        }
    }

    return true;
}

int main() {
    // Input file paths
    std::string rulesFile = "rules.txt";
    std::string updatesFile = "updates.txt";

    try {
        // Parse rules and updates from files
        std::vector<Rule> rules = parseRules(rulesFile);
        std::vector<std::vector<int>> updates = parseUpdates(updatesFile);

        std::vector<std::vector<int>> valid;

        for (auto update : updates) {
            // Create the graph structure and perform the topological sort based on the nodes in the update
            Graph graph;
            InDegree inDegree;

            // Build the graph
            std::cout << "Checking the following update: ";
            for (int i = 0; i < update.size() - 1; i++) {
                //Rule rule = {update[i], update[i + 1]};
                //rules.push_back(rule);
                std::cout << update[i] << ", ";
            }
            std::cout<<std::endl;
        }
        /*
        // Graph structures
        Graph graph;
        InDegree inDegree;

        // Build the graph
        buildGraph(rules, graph, inDegree);

        // Perform topological sort
        std::vector<int> sortedOrder = topologicalSort(graph, inDegree);

        // Output the sorted order
        std::cout << "Topologically Sorted Order: ";
        for (int node : sortedOrder) {
            std::cout << node << " ";
        }
        std::cout << "\n";

        // Validate the updates sequence
        if (validateUpdates(sortedOrder, updates)) {
            std::cout << "The updates sequence is valid.\n";
        } else {
            std::cout << "The updates sequence is invalid.\n";
        }
        */
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
