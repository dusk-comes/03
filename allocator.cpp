#include <cstddef>
#include <memory>
#include <iostream>
#include <utility>
#include <vector>
#include <map>

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
        size_type _preallocated_slots;
};

template <typename T, typename... Args>
Alloc<T, Args...>::Alloc() {}

template <typename T, typename... Args>
Alloc<T, Args...>::Alloc(const Alloc::size_type &elements) : _preallocated_slots{elements} {}

template <typename T, typename... Args>
template <typename U>
Alloc<T, Args...>::Alloc(const Alloc<U, Args...> &alloc) throw() {}

template <typename T, typename... Args>
T* Alloc<T, Args...>::allocate(const Alloc::size_type &elements)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    auto *p = std::malloc(elements * sizeof(T));
    if (!p) throw std::bad_alloc();

    std::cout << "allocated " << elements << " ellements at " << &p << std::endl;

    return reinterpret_cast<T*>(p);
}

template <typename T, typename... Args>
void Alloc<T, Args...>::deallocate(T *p, Alloc::size_type elements)
{
    std::free(p);
}

template <typename T, typename... Args>
typename Alloc<T, Args...>::size_type Alloc<T, Args...>::max_size() const
{
    return _preallocated_slots;
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
    Alloc<int> alloc(3);
    std::vector<int, Alloc<int>> v(alloc);
    for (auto i = 0; i < 3; ++i)
    {
        v.push_back(i);
    }

    Alloc<std::pair<int, int>> map_alloc(4);
    std::map<int, int, std::less<int>, Alloc<std::pair<int, int>>> m(map_alloc);
    m[1] = 666;
        
    return 0;
}
