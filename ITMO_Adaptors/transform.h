#pragma once

template<typename Container, typename Predicate>
class TransformView {
public:
    TransformView(Container& container, Predicate&& predicate)
        : container_(container), predicate_(std::forward<Predicate>(predicate)) {}


    class iterator {
    public:
        iterator(typename Container::iterator iter, Predicate&& predicate) : iter__(iter), predicate__(std::forward<Predicate>(predicate)) {}

        auto operator*() {
            return predicate__(*iter__);
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
        Predicate predicate__;
    };

    // Методы begin() и end() для итерации по представлению
    auto begin() { return iterator(container_.begin(), std::forward<Predicate>(predicate_)); }
    auto end() { return iterator(container_.end(), std::forward<Predicate>(predicate_)); }

private:
    Container container_;
    Predicate predicate_;
};

template<typename Predicate>
class TransformProxy {
public:
    TransformProxy(Predicate&& predicate) : predicate_(std::forward<Predicate>(predicate_)) {}

    template<typename Container>
    auto operator()(Container& container) {
        return TransformView<Container, Predicate>(container, std::forward<Predicate>(predicate_));
    }

private:
    Predicate predicate_;
};

namespace Misha_and_Murad {
    template<typename Predicate>
    TransformProxy<Predicate> transform(Predicate&& predicate) {
        return TransformProxy<Predicate>(std::forward<Predicate>(predicate));
    }
} // namespace Misha_and_Murad
