#include "MyString.hpp"
#include <iostream>

int main() {
    // This main file is for OJ testing
    // The actual test cases will be provided by the OJ system

    // Example usage to ensure compilation
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3 = s1 + s2;

    std::cout << s3.c_str() << std::endl;

    return 0;
}
