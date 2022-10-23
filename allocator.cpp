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
        using size_type = size_t;

        Alloc();
        Alloc(const size_type&);

        template <typename U>
        Alloc(const Alloc<U>&) throw();

        T* allocate(const size_type&);
        
        void deallocate(T*, size_type);

        size_type max_size() const;

    private:
        size_type _preallocated_slots;
};

template <typename T>
Alloc<T>::Alloc() {}

template <typename T>
Alloc<T>::Alloc(const Alloc::size_type &elements) : _preallocated_slots{elements} {}

template <typename T>
template <typename U>
Alloc<T>::Alloc(const Alloc<U> &alloc) throw() {}

template <typename T>
T* Alloc<T>::allocate(const Alloc::size_type &elements)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    auto *p = std::malloc(elements * sizeof(T));
    if (!p) throw std::bad_alloc();

    std::cout << "allocated " << elements << " ellements at " << &p << std::endl;

    return reinterpret_cast<T*>(p);
}

template <typename T>
void Alloc<T>::deallocate(T *p, Alloc::size_type elements)
{
    std::free(p);
}

template <typename T>
typename Alloc<T>::size_type Alloc<T>::max_size() const
{
    return _preallocated_slots;
}

template <class T, class U>
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
    Alloc<int> alloc(3);
    std::vector<int, Alloc<int>> v(alloc);
    for (auto i = 0; i < 3; ++i)
    {
        v.push_back(i);
    }
        
    return 0;
}
