#include <iterator>
#include <memory>
#include <iostream>

template <typename Elem>
struct Link
{
    using pointer = std::shared_ptr<Link<Elem>>;

    Elem val;
    pointer next;

    Link(Elem e, pointer p = nullptr) : val{e}, next{p} {}
};

template <typename T, typename A = std::allocator<T>>
class List
{
    public:
        using pointer = std::shared_ptr<Link<T>>;
        using allocator_type = A;
        using alloc_traits = std::allocator_traits<allocator_type>;

        List();

        pointer push_back(const T &val);
        
        size_t size() const { return _size; }

        class Iterator
        {
            public:
                Iterator(pointer link) : current{link} {}

                Iterator& operator++() { current = current->next; return *this; }

                T& operator*() { return current->val; }

                bool operator==(const Iterator &b) { return current == b.current; }

                bool operator!=(const Iterator &b) { return current != b.current; }


            private:
                pointer current;

        };

        Iterator begin() { return Iterator(first); }
        Iterator end() { return Iterator(nullptr); }

    private:
        pointer last;
        pointer first;
        size_t _size;

};

template<typename T, typename A>
List<T, A>::List() :
    last{nullptr},
    first{nullptr},
    _size{0}
{
}

template <typename T, typename A>
typename List<T,A>::pointer
    List<T, A>::push_back(const T &val)
{
    auto link = std::make_shared<Link<T>>(val);

    if (last == nullptr)
    {
        last = link;
        first = link;
    }
    else
    {
        last->next = link;
        last = link;
    }

    ++_size;
    
    return link;
}