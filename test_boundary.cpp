#include "MyString.hpp"
#include <iostream>
#include <cassert>

int main() {
    // Test exactly SSO_CAPACITY size
    MyString s1("123456789012345");  // Exactly 15 chars
    std::cout << "15 chars: size=" << s1.size() << ", capacity=" << s1.capacity() << std::endl;
    assert(s1.size() == 15);
    assert(s1.capacity() == 15);

    MyString s2("1234567890123456");  // Exactly 16 chars
    std::cout << "16 chars: size=" << s2.size() << ", capacity=" << s2.capacity() << std::endl;
    assert(s2.size() == 16);
    assert(s2.capacity() >= 16);

    // Test resize to exactly SSO boundary
    MyString s3("1234567890123456789");  // 19 chars
    s3.resize(15);
    std::cout << "Resized to 15: size=" << s3.size() << ", capacity=" << s3.capacity() << std::endl;
    assert(s3.size() == 15);
    assert(s3.capacity() == 15);

    MyString s4("12345");
    s4.resize(15);
    std::cout << "Resized from 5 to 15: size=" << s4.size() << ", capacity=" << s4.capacity() << std::endl;
    assert(s4.size() == 15);
    assert(s4.capacity() == 15);

    std::cout << "All boundary tests passed!" << std::endl;
    return 0;
}
