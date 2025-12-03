#include <iostream>


#include "MyOneConnectList.hpp"
#include "MyTwoConnectList.hpp"

template<typename C>
void testContainer(const std::string& name) {
    std::cout << "\n=== " << name << " ===\n";

    C container;

    for (int i = 0; i < 10; i++)
        container.push_back(i);

    for (auto it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "Size: " << container.size() << "\n";

    container.erase(2); 
    container.erase(3);  
    container.erase(4);  

    for (auto it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    container.insert(0, 10);

    for (auto it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    container.insert(4, 20);

    for (auto it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    container.push_back(30);

    for (auto it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}

int main() {
    
    testContainer<MyOneConnectList<int>>("OneConnectList");
    testContainer<MyTwoConnectList<int>>("TwoConnectList");
    
    return 0;
}
