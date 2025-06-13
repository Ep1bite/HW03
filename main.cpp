#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class SimpleVector {
private:
    T* data;
    int currentSize;
    int currentCapacity;

    void reallocate(int newCapacity) {
        if (newCapacity <= currentCapacity) {
            return;
        }

        T* newData = new T[newCapacity];
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        currentCapacity = newCapacity;
    }

public:
    SimpleVector() : data(nullptr), currentSize(0), currentCapacity(10) {
        data = new T[currentCapacity];
    }

    SimpleVector(int capacity) : data(nullptr), currentSize(0), currentCapacity(capacity) {
        if (capacity <= 0) {
            currentCapacity = 10;
        }
        data = new T[currentCapacity];
    }

    SimpleVector(const SimpleVector& other) : data(nullptr), currentSize(other.currentSize), currentCapacity(other.currentCapacity) {
        data = new T[currentCapacity];
        for (int i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }

    ~SimpleVector() {
        delete[] data;
        data = nullptr;
    }

    void push_back(const T& value) {
        if (currentSize == currentCapacity) {
            reallocate(currentCapacity + 5);
        }
        data[currentSize] = value;
        currentSize++;
    }

    void pop_back() {
        if (currentSize > 0) {
            currentSize--;
        }
    }

    int size() const {
        return currentSize;
    }

    int capacity() const {
        return currentCapacity;
    }

    void resize(int newCapacity) {
        if (newCapacity <= currentCapacity) {
            return;
        }
        reallocate(newCapacity);
    }

    void sortData() {
        if (currentSize > 1) {
            std::sort(data, data + currentSize);
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

int main() {
    std::cout << "=== 필수 기능 테스트 ===" << std::endl;
    SimpleVector<int> vec1;
    std::cout << "Initial size: " << vec1.size() << ", capacity: " << vec1.capacity() << std::endl;

    for (int i = 0; i < 5; ++i) {
        vec1.push_back(i * 10);
    }
    std::cout << "After 5 push_back: size: " << vec1.size() << ", capacity: " << vec1.capacity() << std::endl;

    vec1.pop_back();
    std::cout << "After pop_back: size: " << vec1.size() << ", capacity: " << vec1.capacity() << std::endl;

    SimpleVector<std::string> vec2(5);
    std::cout << "vec2 initial size: " << vec2.size() << ", capacity: " << vec2.capacity() << std::endl;

    vec2.push_back("Hello");
    vec2.push_back("World");
    std::cout << "vec2 after push_back: size: " << vec2.size() << ", capacity: " << vec2.capacity() << std::endl;

    std::cout << "\n=== 도전 기능 테스트 ===" << std::endl;

    SimpleVector<int> vec3 = vec1;
    std::cout << "vec3 (copy of vec1) size: " << vec3.size() << ", capacity: " << vec3.capacity() << std::endl;
    try {
        std::cout << "vec3[0]: " << vec3[0] << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error accessing vec3 element: " << e.what() << std::endl;
    }

    SimpleVector<char> charVec(2);
    std::cout << "charVec initial capacity: " << charVec.capacity() << std::endl;
    charVec.push_back('A');
    charVec.push_back('B');
    std::cout << "charVec after 2 push_backs: size: " << charVec.size() << ", capacity: " << charVec.capacity() << std::endl;
    charVec.push_back('C');
    std::cout << "charVec after 3rd push_back (expect resize): size: " << charVec.size() << ", capacity: " << charVec.capacity() << std::endl;
    charVec.push_back('D');
    charVec.push_back('E');
    std::cout << "charVec current elements: ";
    for (int i = 0; i < charVec.size(); ++i) {
        std::cout << charVec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "\nResize function test:" << std::endl;
    SimpleVector<double> doubleVec(3);
    doubleVec.push_back(1.1);
    doubleVec.push_back(2.2);
    doubleVec.push_back(3.3);
    std::cout << "doubleVec before resize: size: " << doubleVec.size() << ", capacity: " << doubleVec.capacity() << std::endl;

    doubleVec.resize(2);
    std::cout << "doubleVec after resize(2) (no change expected): size: " << doubleVec.size() << ", capacity: " << doubleVec.capacity() << std::endl;

    doubleVec.resize(10);
    std::cout << "doubleVec after resize(10) (expect resize): size: " << doubleVec.size() << ", capacity: " << doubleVec.capacity() << std::endl;
    std::cout << "doubleVec elements after resize: ";
    for (int i = 0; i < doubleVec.size(); ++i) {
        std::cout << doubleVec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "\nSortData function test:" << std::endl;
    SimpleVector<int> sortVec(5);
    sortVec.push_back(50);
    sortVec.push_back(10);
    sortVec.push_back(30);
    sortVec.push_back(20);
    sortVec.push_back(40);

    std::cout << "Before sort: ";
    for (int i = 0; i < sortVec.size(); ++i) {
        std::cout << sortVec[i] << " ";
    }
    std::cout << std::endl;

    sortVec.sortData();

    std::cout << "After sort: ";
    for (int i = 0; i < sortVec.size(); ++i) {
        std::cout << sortVec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
