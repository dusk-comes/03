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

template <typename T, size_t S>
class Alloc
{
    public:
        using value_type = T;

        template<typename U, size_t S2>
        struct rebind
        {
            using other = Alloc<U, S2>;
        };

        Alloc();

        template <typename U, size_t S2>
        Alloc(const Alloc<U, S2>&) throw();

        T* allocate(const size_t);
        
        void deallocate(T *p, size_t);

    private:
        size_t _preallocated_slots;
        bool _reserved;
};

template <typename T, size_t S>
Alloc<T, S>::Alloc() : _preallocated_slots{S}, _reserved{false} {}

template <typename T, size_t S1>
template <typename U, size_t S2>
Alloc<T, S1>::Alloc(const Alloc<U, S2> &alloc) throw() {}

template <typename T, size_t S>
T* Alloc<T, S>::allocate(const size_t elements)
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

template <typename T, size_t S>
void Alloc<T, S>::deallocate(T *p, size_t elements)
{
    std::free(p);
}

template <class T, size_t S1, class U, size_t S2>
constexpr bool operator==(const Alloc<T, S1>&, const Alloc<U, S2>&) noexcept
{
    return false;
}

template <class T, size_t S1, class U, size_t S2>
constexpr bool operator!=(const Alloc<T, S1>&, const Alloc<U, S2>&) noexcept
{
    return false;
}

int main()
{
    std::vector<int, Alloc<int, 10>> v;
    for (auto i = 0; i < v.size(); ++i)
        v.push_back(i);

    /*
    for (auto i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ' << std::endl;
        */

    return 0;
}
