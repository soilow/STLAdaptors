#pragma once

#include "transform.h"
#include "filter.h"
#include "take.h"
#include "drop.h"
#include "reverse.h"
#include "keys.h"
#include "values.h"

#include "utils.h"

template<typename Container, typename Predicate>
auto operator|(Container& container, Predicate&& predicate) {
    static_assert(is_stl_container<Container>::value, "Adaptors work only with STL containers");
    
    return predicate(container);
}

template<typename Container, typename Predicate>
auto operator|(Container&& container, Predicate&& predicate) {
    static_assert(is_stl_container<Container>::value, "Adaptors work only with STL containers");
    
    return predicate(container);
}
