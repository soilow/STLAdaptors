#pragma once

template<typename Container>
class TakeView {
public:
    TakeView(Container& container, size_t&& count)
        : container_(container), count_(count) {}

    class iterator {
    public:
        iterator(typename Container::iterator iter, Container& container_, size_t* count)
            : iter__(iter), container__(container_), count__(count) {
        }

        auto operator*() {
            return *iter__;
        }

        iterator& operator++() {
            ++iter__;
            Predicate();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter__ != other.iter__;
        }

    private:
        typename Container::iterator iter__;
        size_t* count__;
        Container& container__;
        
        void Predicate() {
            --(*count__);
            
            while (iter__ != container__.end() && *count__ == 0) {
                ++iter__;
            }
        }
        
    };

    auto begin() { return iterator(container_.begin(), container_, &count_); }
    auto end() { return iterator(container_.end(), container_, &count_); }

private:
    Container container_;
    size_t count_;
};

class TakeProxy {
public:
    TakeProxy(size_t&& count) : count_(std::forward<size_t>(count)) {}
    
    template<typename Container>
    auto operator()(Container& container) {
        return TakeView<Container>(container, std::forward<size_t>(count_));
    }
private:
    size_t count_;
};

namespace Misha_and_Murad {
    TakeProxy take(size_t&& count) {
        return TakeProxy(std::forward<size_t>(count));
    }
} // namespace Misha_and_Murad
