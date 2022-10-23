#include <cstddef>
#include <memory>
#include <iostream>
#include <vector>

template <int P>
struct Factorial
{
    static const int value = P * Factorial<P - 1>::value;
};

template <>
struct Factorial<0>
{
    static const int value = 1;
};

template <typename T>
class Alloc
{
    public:
        using value_type = T;

        Alloc();
        Alloc(const size_t&);

        template <typename U>
        Alloc(const Alloc<U>&) throw();

        T* allocate(const size_t);
        
        void deallocate(T *p, size_t);

    private:
        size_t _preallocated_slots;
        bool _reserved;
};

template <typename T>
Alloc<T>::Alloc() {}

template <typename T>
Alloc<T>::Alloc(const size_t &elements) : _preallocated_slots{elements}, _reserved{false} {}

template <typename T>
template <typename U>
Alloc<T>::Alloc(const Alloc<U> &alloc) throw() {}

template <typename T>
T* Alloc<T>::allocate(const size_t elements)
{
    if (!_reserved)
    {
        auto *p = std::malloc(_preallocated_slots * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        _reserved = true;
        return reinterpret_cast<T*>(p);
    }
}

template <typename T>
void Alloc<T>::deallocate(T *p, size_t elements)
{
    std::free(p);
}

template <class T, size_t S1, class U, size_t S2>
constexpr bool operator==(const Alloc<T>&, const Alloc<U>&) noexcept
{
    return false;
}

template <class T, class U>
constexpr bool operator!=(const Alloc<T>&, const Alloc<U>&) noexcept
{
    return false;
}

int main()
{
    Alloc<int> alloc(10);
    std::vector<int, Alloc<int>> v(10, alloc);
    //for (auto i = 0; i < v.size(); ++i)
    //    v.push_back(i);

    /*
    for (auto i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ' << std::endl;
        */

    return 0;
}
