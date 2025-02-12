#pragma once

template<typename Container>
class TakeView {
public:
    using iterator_type = typename Container::iterator;

    TakeView(Container& container, size_t&& count)
            : container_(container),
              count_(std::move(count)),
              begin_(iterator(*this, container.begin())),
              end_(iterator(*this, container.end())) {
        iterator temp = begin_;
                
        while (count_-- && temp != end_) {
            ++temp;
        }
        
        end_ = temp;
    }

    class iterator {
    public:
        iterator(TakeView& take_view, iterator_type iter)
            : take_view__(take_view), iter__(iter) {}
        
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
        TakeView& take_view__;
        iterator_type iter__;
    };
    
    iterator begin() { return begin_; }
    iterator end() { return end_; }

private:
    Container& container_;
    size_t count_;
    
    iterator begin_;
    iterator end_;
};

class TakeProxy {
public:
    TakeProxy(size_t&& count) : count_(std::move(count)) {}
    
    template<typename Container>
    auto operator()(Container& container) {
        return TakeView<Container>(container, std::move(count_));
    }
private:
    size_t count_;
};

namespace Misha_and_Murad {
    TakeProxy take(size_t count) {
        return TakeProxy(std::move(count));
    }
} // namespace Misha_and_Murad
