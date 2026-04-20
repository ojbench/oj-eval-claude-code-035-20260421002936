#include "MyString.hpp"
#include <iostream>
#include <cassert>

void test_const_access(const MyString& s) {
    std::cout << "const access: size=" << s.size() << ", capacity=" << s.capacity() << std::endl;
    std::cout << "c_str: '" << s.c_str() << "'" << std::endl;
    std::cout << "at(0): '" << s.at(0) << "'" << std::endl;
    std::cout << "operator[](0): '" << s[0] << "'" << std::endl;

    for (auto it = s.cbegin(); it != s.cend(); ++it) {
        // iterate
    }
}

int main() {
    const MyString s1("hello");
    test_const_access(s1);

    const MyString s2("this is a long string");
    test_const_access(s2);

    std::cout << "Const tests passed!" << std::endl;
    return 0;
}
