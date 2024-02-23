#include <iostream>
#include <vector>

#include "Counter.h"

int main() {
    std::vector<int> items = {1, 2, 3, 4, 1, 2, 2, 3, 3, 3};
    Counter<int> counter(items);

    std::cout << "Most common elements:" << std::endl;
    for (int item : counter.most_common(4)) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::cout << "Each element of counters:" << std::endl;
    for (const auto& pair : counter) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << "Total count: " << counter.total() << std::endl;

    counter.subtract(2);
    std::cout << "After subtracting 2: " << counter[2] << std::endl;

    std::cout << "Each element of counters:" << std::endl;
    for (const auto& pair : counter) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::vector<int> items2 = {1, 2, 2, 3};
    Counter<int> otherCounter(items2);
    Counter<int> sum = counter + otherCounter;
    std::cout << "Sum of counters:" << std::endl;
    for (const auto& pair : sum) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    Counter<int> negatedCounter = -counter;
    std::cout << "Negated counter:" << std::endl;
    for (const auto& pair : negatedCounter) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}

