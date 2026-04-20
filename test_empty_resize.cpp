#include "MyString.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

void test_empty_and_resize() {
    std::cout << "Test 1: Empty string resize" << std::endl;
    MyString s1;
    std::cout << "Empty string: size=" << s1.size() << ", capacity=" << s1.capacity() << std::endl;
    s1.resize(5);
    std::cout << "After resize(5): size=" << s1.size() << ", capacity=" << s1.capacity() << std::endl;
    assert(s1.size() == 5);
    assert(s1[0] == '\0');
    assert(s1[4] == '\0');
    std::cout << "Pass!\n" << std::endl;

    std::cout << "Test 2: Resize to 0" << std::endl;
    MyString s2("hello");
    s2.resize(0);
    std::cout << "After resize(0): size=" << s2.size() << std::endl;
    assert(s2.size() == 0);
    assert(std::strlen(s2.c_str()) == 0);
    std::cout << "Pass!\n" << std::endl;

    std::cout << "Test 3: Resize 0 to non-zero" << std::endl;
    MyString s3;
    s3.resize(10);
    assert(s3.size() == 10);
    for (size_t i = 0; i < 10; i++) {
        assert(s3[i] == '\0');
    }
    std::cout << "Pass!\n" << std::endl;

    std::cout << "Test 4: Multiple resize operations" << std::endl;
    MyString s4("test");
    s4.resize(10);
    assert(s4.size() == 10);
    s4.resize(20);
    assert(s4.size() == 20);
    s4.resize(5);
    assert(s4.size() == 5);
    s4.resize(15);
    assert(s4.size() == 15);
    s4.resize(3);
    assert(s4.size() == 3);
    assert(std::strncmp(s4.c_str(), "tes", 3) == 0);
    std::cout << "Pass!\n" << std::endl;

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    try {
        test_empty_and_resize();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
