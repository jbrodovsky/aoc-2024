#include <ranges>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (int x : numbers | std::views::filter([](int n) { return n % 2 == 0; })) {
        std::cout << x << " ";
    }
    return 0;
}
