#include "MyString.hpp"
#include <iostream>
#include <cassert>

void test_basic_construction() {
    std::cout << "Testing basic construction..." << std::endl;

    MyString s1;
    assert(s1.size() == 0);
    assert(s1.capacity() == 15);

    MyString s2("hello");
    assert(s2.size() == 5);
    assert(s2.capacity() == 15);

    MyString s3("this is a long string");
    assert(s3.size() == 21);
    assert(s3.capacity() >= 21);

    std::cout << "Basic construction tests passed!" << std::endl;
}

void test_copy_move() {
    std::cout << "Testing copy and move operations..." << std::endl;

    MyString s1("test");
    MyString s2 = s1;
    assert(s2.size() == 4);
    assert(std::strcmp(s2.c_str(), "test") == 0);

    MyString s3 = MyString("another test");
    assert(s3.size() == 12);

    std::cout << "Copy and move tests passed!" << std::endl;
}

void test_capacity_management() {
    std::cout << "Testing capacity management..." << std::endl;

    MyString s1("short");
    assert(s1.capacity() == 15);

    s1.reserve(30);
    assert(s1.capacity() >= 30);
    assert(s1.size() == 5);

    s1.resize(10);
    assert(s1.size() == 10);

    s1.resize(3);
    assert(s1.size() == 3);

    std::cout << "Capacity management tests passed!" << std::endl;
}

void test_append_concat() {
    std::cout << "Testing append and concatenation..." << std::endl;

    MyString s1("hello");
    s1.append(" world");
    assert(std::strcmp(s1.c_str(), "hello world") == 0);

    MyString s2 = MyString("foo") + MyString("bar");
    assert(std::strcmp(s2.c_str(), "foobar") == 0);

    std::cout << "Append and concatenation tests passed!" << std::endl;
}

void test_iterators() {
    std::cout << "Testing iterators..." << std::endl;

    MyString s("abc");
    int count = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        count++;
    }
    assert(count == 3);

    const MyString cs("def");
    count = 0;
    for (auto it = cs.cbegin(); it != cs.cend(); ++it) {
        count++;
    }
    assert(count == 3);

    std::cout << "Iterator tests passed!" << std::endl;
}

int main() {
    try {
        test_basic_construction();
        test_copy_move();
        test_capacity_management();
        test_append_concat();
        test_iterators();

        std::cout << "\nAll tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
