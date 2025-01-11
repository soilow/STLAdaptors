#pragma once

//#include "utils.h"

template<typename Container>
class DropView {
public:
    using iterator_type = typename Container::iterator;
    
    DropView(Container& container, size_t&& count)
        : container_(container),
          count_(std::move(count)),
          begin_(iterator(*this, container.begin())),
          end_(iterator(*this, container.end())) {
              
        while (count_-- && ++begin_ != end_) {}
    }

    class iterator {
    public:
        iterator(DropView& drop_view, iterator_type iter)
            : drop_view__(drop_view),
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
        
        iterator& operator--() {
            --iter__;
            return *this;
        }

        iterator& operator++() {
            ++iter__;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter__ != other.iter__;
        }
         
    private:
        DropView& drop_view__;
        iterator_type iter__;
        size_t* count__;
    };

    auto begin() { return begin_; }
    auto end() { return end_;}

private:
    Container& container_;
    size_t count_;
    
    iterator begin_;
    iterator end_;
};


class DropProxy {
public:
    DropProxy(size_t&& count) : count_(std::move(count)) {}
    
    template<typename Container>
    auto operator()(Container& container) {
        return DropView<Container>(container, std::move(count_));
    }
private:
    size_t count_;
};

namespace Misha_and_Murad {
    DropProxy drop(size_t&& count) {
        return DropProxy(std::move(count));
    }
} // namespace Misha_and_Murad
