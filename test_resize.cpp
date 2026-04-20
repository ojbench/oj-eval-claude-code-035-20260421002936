#include "MyString.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

void test_resize() {
    std::cout << "Testing resize..." << std::endl;

    // Test 1: Resize from small to small (expanding)
    MyString s1("hello");
    std::cout << "s1 initial: size=" << s1.size() << ", capacity=" << s1.capacity() << ", content='" << s1.c_str() << "'" << std::endl;
    s1.resize(10);
    std::cout << "s1 after resize(10): size=" << s1.size() << ", capacity=" << s1.capacity() << ", content='" << s1.c_str() << "'" << std::endl;
    assert(s1.size() == 10);
    assert(std::strlen(s1.c_str()) == 5);  // Original content + '\0' padding
    assert(s1[0] == 'h');
    assert(s1[4] == 'o');
    assert(s1[5] == '\0');
    assert(s1[9] == '\0');

    // Test 2: Resize from small to small (shrinking)
    MyString s2("hello world");
    std::cout << "\ns2 initial: size=" << s2.size() << ", capacity=" << s2.capacity() << ", content='" << s2.c_str() << "'" << std::endl;
    s2.resize(5);
    std::cout << "s2 after resize(5): size=" << s2.size() << ", capacity=" << s2.capacity() << ", content='" << s2.c_str() << "'" << std::endl;
    assert(s2.size() == 5);
    assert(std::strcmp(s2.c_str(), "hello") == 0);

    // Test 3: Resize from small to large (SSO to heap)
    MyString s3("hello");
    std::cout << "\ns3 initial: size=" << s3.size() << ", capacity=" << s3.capacity() << ", content='" << s3.c_str() << "'" << std::endl;
    s3.resize(20);
    std::cout << "s3 after resize(20): size=" << s3.size() << ", capacity=" << s3.capacity() << ", content='" << s3.c_str() << "'" << std::endl;
    assert(s3.size() == 20);
    assert(s3[0] == 'h');
    assert(s3[4] == 'o');
    assert(s3[5] == '\0');
    assert(s3[19] == '\0');

    // Test 4: Resize from large to small (heap to SSO)
    MyString s4("this is a very long string");
    std::cout << "\ns4 initial: size=" << s4.size() << ", capacity=" << s4.capacity() << ", content='" << s4.c_str() << "'" << std::endl;
    s4.resize(10);
    std::cout << "s4 after resize(10): size=" << s4.size() << ", capacity=" << s4.capacity() << ", content='" << s4.c_str() << "'" << std::endl;
    assert(s4.size() == 10);
    assert(s4.capacity() == 15);
    assert(std::strncmp(s4.c_str(), "this is a ", 10) == 0);

    // Test 5: Resize large to larger
    MyString s5("this is a very long string");
    std::cout << "\ns5 initial: size=" << s5.size() << ", capacity=" << s5.capacity() << ", content='" << s5.c_str() << "'" << std::endl;
    s5.resize(30);
    std::cout << "s5 after resize(30): size=" << s5.size() << ", capacity=" << s5.capacity() << ", content='" << s5.c_str() << "'" << std::endl;
    assert(s5.size() == 30);

    std::cout << "\nAll resize tests passed!" << std::endl;
}

int main() {
    try {
        test_resize();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
