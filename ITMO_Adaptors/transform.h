#pragma once

template<typename Container, typename Predicate>
class TransformView {
public:
    using iterator_type = typename Container::iterator;

    TransformView(Container& container, Predicate&& predicate)
        : container_(container),
          predicate_(std::move(predicate)),
          begin_(*this, container.begin()),
          end_(*this, container.end()) {}

    class iterator {
    public:
        iterator(TransformView& transform_view, iterator_type iter)
            : transform_view__(transform_view),
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
            return transform_view__.predicate_(*iter__);
        }

        iterator& operator++() {
            ++iter__;
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
        TransformView& transform_view__;
        iterator_type iter__;
    };

    auto begin() { return begin_; }
    auto end() { return end_; }
    
private:
    Container& container_;
    Predicate predicate_;
    
    iterator begin_;
    iterator end_;
};

template<typename Predicate>
class TransformProxy {
public:
    TransformProxy(Predicate&& predicate) : predicate_(std::move(predicate)) {}

    template<typename Container>
    auto operator()(Container& container) {
        return TransformView<Container, Predicate>(container, std::move(predicate_));
    }
private:
    Predicate predicate_;
};

namespace Misha_and_Murad {
    template<typename Predicate>
    TransformProxy<Predicate> transform(Predicate&& predicate) {
        return TransformProxy<Predicate>(std::move(predicate));
    }
} // namespace Misha_and_Murad

