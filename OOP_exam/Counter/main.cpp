#include <iostream>
#include <vector>

#include "Counter.h"

int main() {
    int myints[] = {1, 2, 3, 3, 2, 1, 2};

    std::vector<int> items = {1, 2, 3, 4, 1, 2, 2, 3, 3, 3};
    Counter<int> counter(items);

    std::cout << "Most common elements:" << std::endl;
    for (int item : counter.most_common(3)) {
        std::cout << item << " ";
    }

    std::vector<int> a(myints, myints + sizeof(myints) / sizeof(int));
    Counter<int> c(a);
    std::cout << c[99] << std::endl;
    for (auto i : c) {
        std::cout << i.first << ", " << i.second << std::endl;
    }
}
