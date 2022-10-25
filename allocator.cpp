#include <cstddef>
#include <cstdlib>
#include <new>
#include <utility>
#include <map>
#include <iostream>

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

template <int S, typename T>
class Alloc
{
    public:
        using value_type = T;
        using size_type = size_t;

        template <typename U>
        struct rebind
        {
            using other = Alloc<S, U>;
        };

        Alloc();

        template <typename U>
        Alloc(const Alloc<S, U>&) throw();

        T* allocate(const size_type&);
        
        void deallocate(T*, size_type);

        size_type max_size() const;

    private:
        size_type _reserved_slots;
        size_type _used;
        void* _memory_begin;
};

template <int S, typename T>
Alloc<S, T>::Alloc() :
    _reserved_slots{S},
    _used{0},
    _memory_begin{nullptr}
{
}

template <int S, typename T>
template <typename U>
Alloc<S, T>::Alloc(const Alloc<S, U> &) throw() {}

template <int S, typename T>
T* Alloc<S, T>::allocate(const Alloc::size_type &elements)
{
    if (_memory_begin == nullptr)
    {
        _memory_begin = std::malloc(sizeof(T) * _reserved_slots);
        _used = elements;
    }
    else if (_used + elements < _reserved_slots)
    {
        _used += elements;
    }
    else
    {
        throw std::bad_alloc();
    }
    return reinterpret_cast<T*>(_memory_begin);
}

template <int S, typename T>
void Alloc<S, T>::deallocate(T *p, Alloc::size_type)
{
    std::free(p);
}

template <int S, typename T>
typename Alloc<S, T>::size_type Alloc<S, T>::max_size() const
{
    return _reserved_slots;
}

template <int S, class T, class U>
constexpr bool operator==(const Alloc<S, T>&, const Alloc<S, U>&) noexcept
{
    return false;
}

template <int S, class T, class U>
constexpr bool operator!=(const Alloc<S, T>&, const Alloc<S, U>&) noexcept
{
    return false;
}

int main()
{
    std::map<int, int, std::less<int>, Alloc<4, std::pair<const int, int>>> m;
    std::cout << "start to fill" << std::endl;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
        
    return 0;
}
