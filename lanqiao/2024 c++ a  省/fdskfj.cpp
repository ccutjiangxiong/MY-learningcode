#include <fstream>
#include <iostream>
#include <string>


int main() {
    std::ifstream file("flag.txt", std::ios::binary); 
    if (!file) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::cout << content;  
    return 0;
}