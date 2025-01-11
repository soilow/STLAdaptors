#pragma once

template<typename Container, typename Predicate>
class FilterView {
public:
    using iterator_type = typename Container::iterator;
    
    FilterView(Container& container, Predicate&& predicate)
        : container_(container),
          predicate_(std::move(predicate)),
          begin_(*this, container.begin()),
          end_(*this, container.end()) {}
    
    class iterator {
    public:
        iterator(FilterView& filter_view, iterator_type iter)
            : filter_view__(filter_view),
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
            ++iter__;
            filter_view__.FindNextValid(*this);
            return *this;
        }
        
        iterator& operator--() {
            --iter__;
            filter_view__.FindPreviousValid(*this);
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter__ != other.iter__;
        }

    private:
        FilterView& filter_view__;
        iterator_type iter__;
    };
    
    auto begin() { return begin_; }
    auto end() { return end_; }
    
private:
    Container& container_;
    Predicate predicate_;
    
    iterator begin_;
    iterator end_;
    
    void FindNextValid(iterator& iter__) {
        while (iter__ != end_ && !predicate_(*iter__)) {
            ++iter__;
        }
    }
    
    void FindPreviousValid(iterator& iter__) {
        while (iter__ != begin_ && !predicate_(*iter__)) {
            --iter__;
        }
    }
};

template<typename Predicate>
class FilterProxy {
public:
    FilterProxy(Predicate&& predicate) : predicate_(std::move(predicate)) {}
    
    template <typename Container>
    auto operator()(Container& container) {
        return FilterView<Container, Predicate>(container, std::move(predicate_));
    }
    
private:
    Predicate predicate_;
};

namespace Misha_and_Murad {
    template<typename Predicate>
    FilterProxy<Predicate> filter(Predicate&& predicate) {
        return FilterProxy<Predicate>(std::move(predicate));
    }
} // namespace Misha_and_Murad

