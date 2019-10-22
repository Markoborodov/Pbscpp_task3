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

template <class T, class S>
struct custom_allocator {
    typedef T value_type;
    custom_allocator() {}
    template <class U, class P> custom_allocator (const custom_allocator<U, P>&) {}
    T* allocate (std::size_t n) {
        S::operator new(n * sizeof(T));
    }
    void deallocate (T* p, std::size_t n) {
        S::operator delete(p, n * sizeof(T));
    }
};

int main()
{
    auto sp = std::allocate_shared<A>(custom_allocator<A, A>());
}