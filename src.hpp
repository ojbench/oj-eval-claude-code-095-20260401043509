#ifndef SRC_HPP
#define SRC_HPP
#include <iostream>

struct Permutation { // 置换
    int* mapping; // 我觉得这里存啥你应该知道
    size_t size; // 上面那个数组的长度

    Permutation(size_t size) {
        // TODO: 初始化一个长度为size的置换，内容为恒等置换。
        this->size = size;
        this->mapping = new int[size];
        for (size_t i = 0; i < size; i++) {
            this->mapping[i] = i;
        }
    }

    Permutation(const int* mapping, size_t size) {
        // TODO: 初始化一个置换，内容为mapping，大小为size
        this->size = size;
        this->mapping = new int[size];
        for (size_t i = 0; i < size; i++) {
            this->mapping[i] = mapping[i];
        }
    }

    // Copy constructor
    Permutation(const Permutation& other) {
        this->size = other.size;
        this->mapping = new int[size];
        for (size_t i = 0; i < size; i++) {
            this->mapping[i] = other.mapping[i];
        }
    }

    // Copy assignment operator
    Permutation& operator=(const Permutation& other) {
        if (this != &other) {
            delete[] mapping;
            this->size = other.size;
            this->mapping = new int[size];
            for (size_t i = 0; i < size; i++) {
                this->mapping[i] = other.mapping[i];
            }
        }
        return *this;
    }

    ~Permutation() {
        // TODO: 析构函数，合理管理你的内存😈
        delete[] mapping;
    }

    void apply(int* permutation) const {
        // TODO：对于大小为size的数组permutation，将置换应用到它上，直接修改permutation指向的数组。
        int* temp = new int[size];
        for (size_t i = 0; i < size; i++) {
            temp[i] = permutation[mapping[i]];
        }
        for (size_t i = 0; i < size; i++) {
            permutation[i] = temp[i];
        }
        delete[] temp;
    }

    Permutation operator*(const Permutation& other) const {
        // TODO: 返回两个置换的乘积，即this*other。保证this和other的大小相同。
        Permutation result(size);
        for (size_t i = 0; i < size; i++) {
            result.mapping[i] = other.mapping[mapping[i]];
        }
        return result;
    }

    Permutation inverse() const {
        // TODO: 返回该置换的逆置换
        Permutation result(size);
        for (size_t i = 0; i < size; i++) {
            result.mapping[mapping[i]] = i;
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Permutation& p) {
        // 这里重载了输出流，使得输出更方便。这里不需要修改代码。
        os << "[";
        for (size_t i = 0; i < p.size; ++i) {
            os << p.mapping[i];
            if (i < p.size - 1) {
                os << " ";
            }
        }
        os << "]";
        return os;
    }
};

struct Transposition { // 对换
    int a, b;

    Transposition() {
        // TODO: 初始化对换为恒等对换
        a = 0;
        b = 0;
    }

    Transposition(int a, int b)  {
        // TODO: 初始化对换为{a,b}
        this->a = a;
        this->b = b;
    }

    void apply(int* permutation, size_t size) const {
        // TODO: 将对换应用permutation上，直接修改permutation指向的数组。保证size>a且size>b。
        int temp = permutation[a];
        permutation[a] = permutation[b];
        permutation[b] = temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const Transposition& t) {
        // 这里重载了输出流，使得输出更方便。这里不需要修改代码。
        os << "{" << t.a << " " << t.b << "}";
        return os;
    }

    Permutation toPermutation(size_t size) const {
        // TODO: 将对换转换为大小为size的置换。保证size>a且size>b。返回一个置换。
        Permutation result(size);
        result.mapping[a] = b;
        result.mapping[b] = a;
        return result;
    }
};

struct Cycle { // 轮换
    int* elements;// 我也觉得这里存啥你应该知道
    size_t size;

    Cycle(const int* elements, size_t size) {
        // TODO: 初始化一个轮换，内容为elements，大小为size
        this->size = size;
        this->elements = new int[size];
        for (size_t i = 0; i < size; i++) {
            this->elements[i] = elements[i];
        }
    }

    // Copy constructor
    Cycle(const Cycle& other) {
        this->size = other.size;
        this->elements = new int[size];
        for (size_t i = 0; i < size; i++) {
            this->elements[i] = other.elements[i];
        }
    }

    // Copy assignment operator
    Cycle& operator=(const Cycle& other) {
        if (this != &other) {
            delete[] elements;
            this->size = other.size;
            this->elements = new int[size];
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    ~Cycle() {
        // TODO: 析构函数，合理管理你的内存😈
        delete[] elements;
    }

    void apply(int* permutation, size_t size) const {
        // TODO: 将轮换应用大小为size的permutation上，直接修改permutation指向的数组。保证size>=elements[i]。
        if (this->size == 0) return;

        int last_value = permutation[elements[this->size - 1]];
        for (size_t i = this->size - 1; i > 0; i--) {
            permutation[elements[i]] = permutation[elements[i - 1]];
        }
        permutation[elements[0]] = last_value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cycle& c) {
        // 这里重载了输出流，使得输出更方便。这里不需要修改代码。
        os << "{";
        for (size_t i = 0; i < c.size; ++i) {
            os << c.elements[i];
            if (i < c.size - 1) {
                os << " ";
            }
        }
        os << "}";
        return os;
    }

    Permutation toPermutation(size_t size) const {
        // TODO: 将轮换转换为大小为size的置换。保证size>=elements[i]。返回一个置换。
        Permutation result(size);
        for (size_t i = 0; i < this->size; i++) {
            result.mapping[elements[i]] = elements[(i + 1) % this->size];
        }
        return result;
    }
};


#endif
