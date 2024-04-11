//#pragma once
//
//template<typename Range, typename Func>
//class FilterView {
//public:
//    FilterView(Range&& range, Func&& func)
//        : range_(std::forward<Range>(range)), func_(std::forward<Func>(func)) {}
//
//    // Внутренний класс-итератор для представления
//    class iterator {
//    public:
//        iterator(typename std::remove_reference_t<Range>::iterator it, Func func, Range& range)
//            : it_(it), func_(std::move(func)), range_(range) {
//            find_next_valid(); // Поиск первого элемента, удовлетворяющего условию
//        }
//
//        auto operator*() {
//            return *it_;
//        }
//
//        iterator& operator++() {
//            ++it_;
//            find_next_valid();
//            return *this;
//        }
//
//        bool operator!=(const iterator& other) const {
//            return it_ != other.it_;
//        }
//
//    private:
//        void find_next_valid() {
//            while (it_ != range_.end() && !func_(*it_)) {
//                ++it_;
//            }
//        }
//
//        typename std::remove_reference_t<Range>::iterator it_;
//        Func func_;
//        Range& range_;
//    };
//
//    // Методы begin() и end() для итерации по представлению
//    auto begin() { return iterator(range_.begin(), func_, range_); }
//    auto end() { return iterator(range_.end(), func_, range_); }
//
//
//private:
//    Range range_;
//    Func func_;
//};
//
//
//
//
//template<typename Func>
//class FilterViewBuilder {
//public:
//    FilterViewBuilder(Func&& func) : func_(std::forward<Func>(func)) {}
//
//    template <typename Range>
//    auto operator()(Range&& range) {
//        return FilterView<Range, Func>(std::forward<Range>(range), std::forward<Func>(func_));
//    }
//
//private:
//    Func func_;
//};
//
//template<typename Func>
//FilterViewBuilder<Func> filter(Func&& func) {
//    return FilterViewBuilder<Func>(std::forward<Func>(func));
//}
//


#pragma once

template<typename Container, typename Predicate>
class FilterView {
public:
    FilterView(Container& container, Predicate&& predicate)
        : container_(container), predicate_(std::forward<Predicate>(predicate_)) {}

    // Внутренний класс-итератор для представления
    class iterator {
    public:
        iterator(typename Container::iterator iter, Predicate&& predicate_, Container& container_)
            : iter__(iter), predicate__(std::forward<Predicate>(predicate_)), container__(container_) {
            find_next_valid(); // Поиск первого элемента, удовлетворяющего условию
        }
        
        auto operator*() {
            return *iter__;
        }

        iterator& operator++() {
            ++iter__;
            find_next_valid();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter__ != other.iter__;
        }

    private:
        void find_next_valid() {
            while (iter__ != container__.end() && !predicate__(*iter__)) {
                ++iter__;
            }
        }
        
//        typename std::remove_reference_t<Range>::iterator it_;
        typename Container::iterator iter__;
        Predicate predicate__;
        Container& container__;
    };

    // Методы begin() и end() для итерации по представлению
    auto begin() { return iterator(container_.begin(), std::forward<Predicate>(predicate_), container_); }
    auto end() { return iterator(container_.end(), std::forward<Predicate>(predicate_), container_); }


private:
    Container container_;
    Predicate predicate_;
};

template<typename Predicate>
class FilterProxy {
public:
    FilterProxy(Predicate&& predicate) : predicate_(std::forward<Predicate>(predicate)) {}
    
    template <typename Container>
    auto operator()(Container& container) {
        return FilterView<Container, Predicate>(container, std::forward<Predicate>(predicate_));
    }
    
private:
    Predicate predicate_;
};

namespace Misha_and_Murad {
    template<typename Predicate>
    FilterProxy<Predicate> filter(Predicate&& predicate) {
        return FilterProxy<Predicate>(std::forward<Predicate>(predicate));
    }
} // namespace Misha_and_Murad

