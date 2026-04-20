#ifndef SIMPLE_STRING_SIMPLESTRING_HPP
#define SIMPLE_STRING_SIMPLESTRING_HPP

#include <stdexcept>
#include <cstring>

class MyString {
private:
    static constexpr size_t SSO_CAPACITY = 15;

    union {
        char* heap_ptr;
        char small_buffer[16];
    };

    size_t str_size;
    size_t str_capacity;

    bool is_sso() const {
        return str_capacity == SSO_CAPACITY;
    }

    char* get_data() {
        return is_sso() ? small_buffer : heap_ptr;
    }

    const char* get_data() const {
        return is_sso() ? small_buffer : heap_ptr;
    }

public:
    MyString() : str_size(0), str_capacity(SSO_CAPACITY) {
        small_buffer[0] = '\0';
    }

    MyString(const char* s) {
        if (s == nullptr) {
            str_size = 0;
            str_capacity = SSO_CAPACITY;
            small_buffer[0] = '\0';
            return;
        }

        str_size = std::strlen(s);

        if (str_size <= SSO_CAPACITY) {
            str_capacity = SSO_CAPACITY;
            std::memcpy(small_buffer, s, str_size + 1);
        } else {
            str_capacity = str_size;
            heap_ptr = new char[str_capacity + 1];
            std::memcpy(heap_ptr, s, str_size + 1);
        }
    }

    MyString(const MyString& other) {
        str_size = other.str_size;
        str_capacity = other.str_capacity;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, str_size + 1);
        } else {
            heap_ptr = new char[str_capacity + 1];
            std::memcpy(heap_ptr, other.heap_ptr, str_size + 1);
        }
    }

    MyString(MyString&& other) noexcept {
        str_size = other.str_size;
        str_capacity = other.str_capacity;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, str_size + 1);
        } else {
            heap_ptr = other.heap_ptr;
            other.heap_ptr = nullptr;
        }

        other.str_size = 0;
        other.str_capacity = SSO_CAPACITY;
        other.small_buffer[0] = '\0';
    }

    MyString& operator=(MyString&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (!is_sso()) {
            delete[] heap_ptr;
        }

        str_size = other.str_size;
        str_capacity = other.str_capacity;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, str_size + 1);
        } else {
            heap_ptr = other.heap_ptr;
            other.heap_ptr = nullptr;
        }

        other.str_size = 0;
        other.str_capacity = SSO_CAPACITY;
        other.small_buffer[0] = '\0';

        return *this;
    }

    MyString& operator=(const MyString& other) {
        if (this == &other) {
            return *this;
        }

        if (!is_sso()) {
            delete[] heap_ptr;
        }

        str_size = other.str_size;
        str_capacity = other.str_capacity;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, str_size + 1);
        } else {
            heap_ptr = new char[str_capacity + 1];
            std::memcpy(heap_ptr, other.heap_ptr, str_size + 1);
        }

        return *this;
    }

    ~MyString() {
        if (!is_sso()) {
            delete[] heap_ptr;
        }
    }

    const char* c_str() const {
        return get_data();
    }

    size_t size() const {
        return str_size;
    }

    size_t capacity() const {
        return str_capacity;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= str_capacity) {
            return;
        }

        if (new_capacity <= SSO_CAPACITY && is_sso()) {
            return;
        }

        char* new_data = new char[new_capacity + 1];
        std::memcpy(new_data, get_data(), str_size + 1);

        if (!is_sso()) {
            delete[] heap_ptr;
        }

        heap_ptr = new_data;
        str_capacity = new_capacity;
    }

    void resize(size_t new_size) {
        if (new_size == str_size) {
            return;
        }

        if (new_size <= SSO_CAPACITY) {
            if (!is_sso()) {
                char temp[SSO_CAPACITY + 1];
                std::memcpy(temp, heap_ptr, (new_size < str_size ? new_size : str_size) + 1);
                delete[] heap_ptr;
                std::memcpy(small_buffer, temp, (new_size < str_size ? new_size : str_size) + 1);
                str_capacity = SSO_CAPACITY;
            }
            if (new_size > str_size) {
                std::memset(small_buffer + str_size, '\0', new_size - str_size);
            }
            small_buffer[new_size] = '\0';
        } else {
            if (new_size > str_capacity) {
                reserve(new_size);
            }
            if (new_size > str_size) {
                std::memset(get_data() + str_size, '\0', new_size - str_size);
            }
            get_data()[new_size] = '\0';
        }

        str_size = new_size;
    }

    char& operator[](size_t index) {
        return get_data()[index];
    }

    MyString operator+(const MyString& rhs) const {
        size_t new_size = str_size + rhs.str_size;
        MyString result;

        if (new_size <= SSO_CAPACITY) {
            result.str_capacity = SSO_CAPACITY;
            std::memcpy(result.small_buffer, get_data(), str_size);
            std::memcpy(result.small_buffer + str_size, rhs.get_data(), rhs.str_size);
            result.small_buffer[new_size] = '\0';
        } else {
            result.str_capacity = new_size;
            result.heap_ptr = new char[new_size + 1];
            std::memcpy(result.heap_ptr, get_data(), str_size);
            std::memcpy(result.heap_ptr + str_size, rhs.get_data(), rhs.str_size);
            result.heap_ptr[new_size] = '\0';
        }

        result.str_size = new_size;
        return result;
    }

    void append(const char* str) {
        if (str == nullptr || *str == '\0') {
            return;
        }

        size_t append_len = std::strlen(str);
        size_t new_size = str_size + append_len;

        if (new_size > str_capacity) {
            size_t new_capacity = str_capacity;
            if (new_capacity == 0) {
                new_capacity = 1;
            }
            while (new_capacity < new_size) {
                new_capacity = new_capacity * 2;
            }
            reserve(new_capacity);
        }

        std::memcpy(get_data() + str_size, str, append_len + 1);
        str_size = new_size;
    }

    const char& at(size_t pos) const {
        if (pos >= str_size) {
            throw std::out_of_range("Index out of range");
        }
        return get_data()[pos];
    }

    class const_iterator;

    class iterator {
    private:
        char* ptr;

    public:
        iterator(char* p = nullptr) : ptr(p) {}

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }

        iterator& operator--() {
            --ptr;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --ptr;
            return temp;
        }

        char& operator*() const {
            return *ptr;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator==(const const_iterator& other) const;

        bool operator!=(const const_iterator& other) const;

        friend class const_iterator;
    };

    class const_iterator {
    private:
        const char* ptr;

    public:
        const_iterator(const char* p = nullptr) : ptr(p) {}

        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++ptr;
            return temp;
        }

        const_iterator& operator--() {
            --ptr;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator temp = *this;
            --ptr;
            return temp;
        }

        const char& operator*() const {
            return *ptr;
        }

        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        friend class iterator;
    };

    iterator begin() {
        return iterator(get_data());
    }

    iterator end() {
        return iterator(get_data() + str_size);
    }

    const_iterator cbegin() const {
        return const_iterator(get_data());
    }

    const_iterator cend() const {
        return const_iterator(get_data() + str_size);
    }
};

inline bool MyString::iterator::operator==(const const_iterator& other) const {
    return ptr == other.ptr;
}

inline bool MyString::iterator::operator!=(const const_iterator& other) const {
    return ptr != other.ptr;
}

#endif
