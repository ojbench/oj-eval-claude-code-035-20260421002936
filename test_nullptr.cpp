#include "MyString.hpp"
#include <iostream>
#include <cassert>

int main() {
    // Test nullptr
    MyString s1(nullptr);
    std::cout << "nullptr: size=" << s1.size() << ", content='" << s1.c_str() << "'" << std::endl;
    assert(s1.size() == 0);

    // Test empty string
    MyString s2("");
    std::cout << "empty: size=" << s2.size() << ", content='" << s2.c_str() << "'" << std::endl;
    assert(s2.size() == 0);

    std::cout << "Tests passed!" << std::endl;
    return 0;
}
