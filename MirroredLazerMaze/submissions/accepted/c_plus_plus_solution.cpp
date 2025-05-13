#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}

