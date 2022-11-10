#include <cstddef>
#include <cstdlib>
#include <new>
#include <iostream>

#if DEBUG == 1
    #define PRINT(key, value) (std::cout << key << " : " << value << std::endl)
#else
    #define PRINT(...) do {} while(0)
#endif

template <typename M>
struct Block
{
    M *start;
    size_t end;

    ~Block()
    {
        std::free(start);
    }
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
        ~Alloc();

        template <typename U>
        Alloc(const Alloc<S, U>&) throw();

        T* allocate(const size_type&);
        
        void deallocate(T*, size_type);

        size_type max_size() const;

    private:
        Block<T> mem;
        size_type offset;
};

template <int S, typename T>
Alloc<S, T>::Alloc() :
    mem{nullptr, 0},
    offset{0}
{
}

template <int S, typename T>
Alloc<S, T>::~Alloc()
{
}


template <int S, typename T>
template <typename U>
Alloc<S, T>::Alloc(const Alloc<S, U> &) throw() {}

template <int S, typename T>
T* Alloc<S, T>::allocate(const Alloc::size_type &elements)
{
    if (mem.start == nullptr)
    {
        mem.start = reinterpret_cast<T*>(std::malloc(sizeof(T) * S));
        mem.end = S;

        PRINT("_memory_begin at ", mem.start);
        PRINT("_memory_end at ", &(mem.start[S]));
    }
    else if (offset + elements < mem.end)
    {
        offset += elements;
    }
    else
    {
        throw std::bad_alloc();
    }

    PRINT("_memory_used at ", &mem.start[offset]);

    return &mem.start[offset];
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
