#include <iostream>
#include <memory>

class A {
public:
    // ...
    static void* operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }

    static void operator delete(void* p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

int main()
{
    auto sp = std::make_shared<A>();
}