#pragma once

#include "utils.h"

template<typename Container>
class ValuesView {
public:
    using iterator_type = typename Container::iterator;
    
    ValuesView(Container& container)
        : container_(container),
          begin_(iterator(*this, container.begin())),
          end_(iterator(*this, container.end())) {}
    
    class iterator {
    public:
        iterator(ValuesView& values_view, iterator_type iter) : values_view__(values_view), iter__(iter) {}

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
            return iter__->second;
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
        ValuesView& values_view__;
        iterator_type iter__;
    };
    
    auto begin() { return begin_; }
    auto end() { return end_; }
    
private:
    Container& container_;
    
    iterator begin_;
    iterator end_;
};


class ValuesProxy {
public:
    ValuesProxy(){}

    template<typename Container>
    auto operator()(Container& container) {
        static_assert(is_associative_container<Container>::value, "Adaptor Values works only with associative container");
        
        return ValuesView<Container>(container);
    }
};

namespace Misha_and_Murad {
    ValuesProxy values() {
        return ValuesProxy();
    }
} // namespace Misha_and_Murad



