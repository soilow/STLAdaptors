#pragma once

#include "utils.h"

template<typename Container>
class KeysView {
public:
    using iterator_type = typename Container::iterator;
    
    KeysView(Container& container)
        : container_(container),
          begin_(iterator(*this, container.begin())),
          end_(iterator(*this, container.end())) {}
    
    class iterator {
    public:
        iterator(KeysView& keys_view, iterator_type iter) : keys_view__(keys_view), iter__(iter) {}

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
            return iter__->first;
        }

        iterator& operator++() {
            ++iter__;
            return *this;
        }
        
        iterator& operator--() {
            ++iter__;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter__ != other.iter__;
        }
        
    private:
        KeysView& keys_view__;
        iterator_type iter__;
    };
    
    auto begin() { return begin_; }
    auto end() { return end_; }
    
private:
    Container& container_;
    
    iterator begin_;
    iterator end_;
};


class KeysProxy {
public:
    KeysProxy(){}

    template<typename Container>
    auto operator()(Container& container) {
        static_assert(is_associative_container<Container>::value, "Adaptor Keys works only with associative container");
        
        return KeysView<Container>(container);
    }
};

namespace Misha_and_Murad {
    KeysProxy keys() {
        return KeysProxy();
    }
} // namespace Misha_and_Murad



