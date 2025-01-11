#pragma once

template<typename Container>
class ReverseView {
public:
    using iterator_type = typename Container::iterator;

    ReverseView(Container& container)
        : container_(container),
          begin_(iterator(*this, --container.end())),
          end_(iterator(*this, --container.begin())) {}

    class iterator {
    public:
        iterator(ReverseView& reverse_view, iterator_type iter)
            : reverse_view__(reverse_view),
              iter__(iter) {}
        
        ~iterator()                            = default;
        iterator(const iterator& other)        = default;
        iterator(iterator&& other)             = default;
        iterator& operator=(iterator&& other)  = default;
        
        iterator& operator=(const iterator& other) {
            if (this != &other) {
                iter__ = other.iter__;
            }
            
            return *this;
        }
        
        auto operator*() {
            return *iter__;
        }

        iterator& operator++() {
            --iter__;
            return *this;
        }
        
        iterator& operator--() {
            --iter__;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter__ != other.iter__;
        }
        
    private:
        iterator_type iter__;
        ReverseView& reverse_view__;
    };
    
    auto begin() {return begin_; }
    auto end() {return end_; }
    
private:
    Container& container_;
    
    iterator begin_;
    iterator end_;
};

class ReverseProxy {
public:
    ReverseProxy(){}

    template<typename Container>
    auto operator()(Container& container) {
        return ReverseView<Container>(container);
    }
};

namespace Misha_and_Murad {
    ReverseProxy reverse() {
        return ReverseProxy();
    }
} // namespace Misha_and_Murad



