#include "MyString.hpp"
#include <iostream>
#include <cassert>

void test_resize_iteration() {
    std::cout << "Testing resize with iteration..." << std::endl;

    MyString s("abc");
    s.resize(6);

    std::cout << "After resize(6), size=" << s.size() << std::endl;
    assert(s.size() == 6);

    // Check each character
    assert(s[0] == 'a');
    assert(s[1] == 'b');
    assert(s[2] == 'c');
    assert(s[3] == '\0');
    assert(s[4] == '\0');
    assert(s[5] == '\0');

    // Test with at()
    assert(s.at(0) == 'a');
    assert(s.at(2) == 'c');
    assert(s.at(3) == '\0');
    assert(s.at(5) == '\0');

    // Test iteration
    int count = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        count++;
    }
    assert(count == 6);

    std::cout << "All iteration tests passed!" << std::endl;
}

int main() {
    try {
        test_resize_iteration();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
