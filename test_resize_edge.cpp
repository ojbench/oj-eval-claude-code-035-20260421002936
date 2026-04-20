#include "MyString.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

void test_resize_edge_cases() {
    std::cout << "Testing resize edge cases..." << std::endl;

    // Test resize to 0
    MyString s1("hello");
    s1.resize(0);
    std::cout << "s1 after resize(0): size=" << s1.size() << ", content='" << s1.c_str() << "'" << std::endl;
    assert(s1.size() == 0);
    assert(std::strlen(s1.c_str()) == 0);

    // Test resize to same size
    MyString s2("test");
    s2.resize(4);
    assert(s2.size() == 4);
    assert(std::strcmp(s2.c_str(), "test") == 0);

    // Test multiple resizes
    MyString s3("abc");
    s3.resize(10);
    assert(s3.size() == 10);
    s3.resize(5);
    assert(s3.size() == 5);
    s3.resize(8);
    assert(s3.size() == 8);

    // Test resize from heap to SSO boundary
    MyString s4("1234567890123456");  // 16 chars, on heap
    std::cout << "s4 initial: size=" << s4.size() << ", capacity=" << s4.capacity() << std::endl;
    s4.resize(15);  // Exactly SSO boundary
    std::cout << "s4 after resize(15): size=" << s4.size() << ", capacity=" << s4.capacity() << std::endl;
    assert(s4.size() == 15);
    assert(s4.capacity() == 15);
    assert(std::strncmp(s4.c_str(), "123456789012345", 15) == 0);

    // Test resize from SSO to heap boundary
    MyString s5("123456789012345");  // 15 chars, in SSO
    std::cout << "s5 initial: size=" << s5.size() << ", capacity=" << s5.capacity() << std::endl;
    s5.resize(16);  // Just over SSO boundary
    std::cout << "s5 after resize(16): size=" << s5.size() << ", capacity=" << s5.capacity() << std::endl;
    assert(s5.size() == 16);
    assert(s5.capacity() >= 16);
    assert(std::strncmp(s5.c_str(), "123456789012345", 15) == 0);
    assert(s5[15] == '\0');

    std::cout << "All edge case tests passed!" << std::endl;
}

int main() {
    try {
        test_resize_edge_cases();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
