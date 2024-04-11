#include <iostream>
#include <vector>
#include <set>

#include "ITMO_Adaptors/adaptors.h"

using namespace Misha_and_Murad;

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    for (int i: v | drop(2) | take(3)) {
        std::cout << i << " ";
    }

    for (int i: v | Misha_and_Murad::drop(2)
                  | Misha_and_Murad::filter([](int x){return !(x & 1);})
                  | Misha_and_Murad::transform([](int x){return x * 2;})
                  | Misha_and_Murad::take(5)) {
        std::cout << i << " ";
    }

    return 0;
}
