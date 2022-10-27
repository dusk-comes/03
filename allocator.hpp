#include <cstddef>
#include <cstdlib>
#include <new>

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
        ~Alloc();

        template <typename U>
        Alloc(const Alloc<S, U>&) throw();

        T* allocate(const size_type&);
        
        void deallocate(T*, size_type);

        size_type max_size() const;

    private:
        T *_memory_begin;
        T *_memory_end;
        T *_memory_used;
};

template <int S, typename T>
Alloc<S, T>::Alloc() :
    _memory_begin{nullptr},
    _memory_end{nullptr},
    _memory_used{nullptr}
{
}

template <int S, typename T>
Alloc<S, T>::~Alloc()
{
    std::free(_memory_begin);
    _memory_used = nullptr;
    _memory_end = nullptr;
}


template <int S, typename T>
template <typename U>
Alloc<S, T>::Alloc(const Alloc<S, U> &) throw() {}

template <int S, typename T>
T* Alloc<S, T>::allocate(const Alloc::size_type &elements)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if (_memory_begin == nullptr)
    {
        _memory_begin = reinterpret_cast<T*>(std::malloc(sizeof(T) * S));
        _memory_used = _memory_begin;
        _memory_end = _memory_begin + S * sizeof(T);

        std::cout << "_memory_begin at " << &_memory_begin << std::endl;
        std::cout << "_memory_end at " << &_memory_end << std::endl;
    }
    else if (_memory_used + elements * sizeof(T) < _memory_end)
    {
        _memory_used += elements * sizeof(T);
    }
    else
    {
        throw std::bad_alloc();
    }

    std::cout << "_memory_used at " << &_memory_used << std::endl;
    return _memory_used;
}

template <int S, typename T>
void Alloc<S, T>::deallocate(T*, Alloc::size_type)
{
}

template <int S, typename T>
typename Alloc<S, T>::size_type Alloc<S, T>::max_size() const
{
    return S;
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
