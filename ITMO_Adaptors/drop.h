#pragma once

template<typename Container>
class DropView {
public:
    DropView(Container& container, size_t&& count)
        : container_(container), count_(count) {}

    class iterator {
    public:
        iterator(typename Container::iterator iter, Container& container_, size_t* count)
            : iter__(iter), container__(container_), count__(count) {
                while (iter__ != container__.end() && *count__) {
                    ++iter__;
                    --(*count__);
                }
        }

        auto operator*() {
            return *iter__;
        }

        iterator& operator++() {
            ++iter__;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter__ != other.iter__;
        }

    private:
        typename Container::iterator iter__;
        size_t* count__;
        Container& container__;
    };

    auto begin() { return iterator(container_.begin(), container_, &count_); }
    auto end() { return iterator(container_.end(), container_, &count_); }

private:
    Container container_;
    size_t count_;
};


class DropProxy {
public:
    DropProxy(size_t&& count) : count_(std::forward<size_t>(count)) {}
    
    template<typename Container>
    auto operator()(Container& container) {
        return DropView<Container>(container, std::forward<size_t>(count_));
    }
private:
    size_t count_;
};

namespace Misha_and_Murad {
    DropProxy drop(size_t&& count) {
        return DropProxy(std::forward<size_t>(count));
    }
} // namespace Misha_and_Murad
