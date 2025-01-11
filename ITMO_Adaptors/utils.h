#pragma once

#include <map>
#include <set>

// Проверка на STL-контейнер
template <typename T>
struct is_stl_container {
private:
    template <typename U>
    static constexpr bool check(...) {
        return false;
    }
    
    template <typename U>
    static constexpr auto check(U* ptr) -> decltype(
        ptr->begin(),
        ptr->end(),
        ++std::declval<decltype(ptr->begin())&>(),
        --std::declval<decltype(ptr->end())&>(),
        std::true_type{}
    ) {
        return {};
    }
    
public:
    static constexpr bool value = check<T>(nullptr);
};

template<typename T>
struct is_associative_container : std::false_type {};

template<typename Key, typename Value, typename Compare, typename Allocator>
struct is_associative_container<std::map<Key, Value, Compare, Allocator>> : std::true_type {};

template<typename Key, typename Compare, typename Allocator>
struct is_associative_container<std::set<Key, Compare, Allocator>> : std::true_type {};
