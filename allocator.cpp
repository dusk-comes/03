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

template <typename T, typename... Args>
class Alloc
{
    public:
        using value_type = T;
        using size_type = size_t;

        Alloc();
        Alloc(const size_type&);

        template <typename U>
        Alloc(const Alloc<U, Args...>&) throw();

        T* allocate(const size_type&);
        
        void deallocate(T*, size_type);

        size_type max_size() const;

    private:
        size_type _reserved_slots;
        size_type _used;
        void* _memory_begin;
};

template <typename T, typename... Args>
Alloc<T, Args...>::Alloc() {}

template <typename T, typename... Args>
Alloc<T, Args...>::Alloc(const Alloc::size_type &elements) :
    _reserved_slots{elements},
    _used{0},
    _memory_begin{nullptr}
{
}

template <typename T, typename... Args>
template <typename U>
Alloc<T, Args...>::Alloc(const Alloc<U, Args...> &) throw() {}

template <typename T, typename... Args>
T* Alloc<T, Args...>::allocate(const Alloc::size_type &elements)
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

template <typename T, typename... Args>
void Alloc<T, Args...>::deallocate(T *p, Alloc::size_type)
{
    std::free(p);
}

template <typename T, typename... Args>
typename Alloc<T, Args...>::size_type Alloc<T, Args...>::max_size() const
{
    return _reserved_slots;
}

template <class T, class U, typename... Args>
constexpr bool operator==(const Alloc<T, Args...>&, const Alloc<U, Args...>&) noexcept
{
    return false;
}

template <class T, class U, typename... Args>
constexpr bool operator!=(const Alloc<T, Args...>&, const Alloc<U, Args...>&) noexcept
{
    return false;
}

int main()
{
    Alloc<std::pair<int, int>> map_alloc(4);
    std::map<int, int, std::less<int>, Alloc<std::pair<int, int>>> m(map_alloc);
    std::cout << "start to fill" << std::endl;
    m[1] = 1;
    //m[2] = 2;
    //m[3] = 3;
        
    return 0;
}
