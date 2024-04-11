#pragma once

#include "transform.h"
#include "filter.h"
#include "take.h"
#include "drop.h"

template<typename Container, typename Predicate>
auto operator|(Container& container, Predicate&& predicate) {
    return predicate(container);
}

template<typename Container, typename Predicate>
auto operator|(Container&& container, Predicate&& predicate) {
    return predicate(container);
}








//template<typename Range>
//class Reverse {
//public:
//    Reverse(Range&& range)
//        : range_(std::forward<Range>(range)) {}
//
//    // Внутренний класс-итератор для представления
//    class iterator {
//    public:
//        iterator(typename std::remove_reference_t<Range>::iterator it)
//            : it_(it) {
//
//        }
//
//        auto operator*() {
//            return *it_;
//        }
//
//        iterator& operator++() {
//            ++it_;
//            return *this;
//        }
//
//        bool operator!=(const iterator& other) const {
//            return it_ != other.it_;
//        }
//
//    private:
//        typename std::remove_reference_t<Range>::iterator it_;
//    };
//
//    // Методы begin() и end() для итерации по представлению
//    auto begin() { return iterator(range_.end()); }
//    auto end() { return iterator(range_.begin()); }
//
//private:
//    Range range_;
//};
//
//
//class ReverseProxy {
//public:
//    ReverseProxy(){}
//
//    template<typename Container>
//    auto operator()(Container&& container) {
//        return Reverse<Container>(std::forward<Container>(container));
//    }
//};
//
//ReverseProxy reverse() {
//    return ReverseProxy();
//}
//


