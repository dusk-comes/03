#include <memory>

template <typename Elem>
struct Link
{
    using link_pointer = std::shared_ptr<Link<Elem>>;

    Elem val;
    link_pointer next;

    Link(Elem e, link_pointer p = nullptr) : val{e}, next{p} {}
};

template <typename T, typename A = std::allocator<T>>
class List
{
    public:
        using link_pointer = std::shared_ptr<Link<T>>;
        using allocator_type = A;
        using alloc_traits = std::allocator_traits<allocator_type>;

        List();

        link_pointer push_back(const T &val);

    private:
        link_pointer last;

};

template<typename T, typename A>
List<T, A>::List() :
    last{nullptr}
{
}

template <typename T, typename A>
typename List<T,A>::link_pointer
    List<T, A>::push_back(const T &val)
{
    auto link = std::make_shared<Link<T>>(val);

    if (last == nullptr)
    {
        last = link;
    }
    else
    {
        last->next = link;
        last = link;
    }
    
    return link;
}
