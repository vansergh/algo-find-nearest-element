//https://pastebin.com/Z5U1Z3i5
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement_(const set<int>& numbers, int border) {
    // set<int>::const_iterator — тип итераторов для константного множества целых чисел
    //return FindNearestElement(numbers.begin(), numbers.end(), border);
    auto MaxIt = [](const auto& left, const auto& right) {
        return *left > *right ? left : right;
    };
    auto MinIt = [](const auto& left, const auto& right) {
        return *left < *right ? left : right;
    };    
    const auto begin = numbers.begin();
    const auto end = numbers.end();
    if (begin == end) { // container is empty returning end
        return end;
    }
    std::size_t size = std::distance(begin, end); // size of container between iterators
    if (size == 1) { // returning element if there is only one element
        return begin;
    }
    const auto mid = std::next(begin, size / 2);
    if (*mid == border) { // found at middle position
        return mid;   
    }
    else if (*mid > border) { // go left recursively
        const set<int> tmp(begin, mid);

        const auto return_it = FindNearestElement_(tmp, border);
        const auto return_begin = tmp.begin();
        const size_t index = std::distance(return_begin, return_it);
        
        const auto left_it = std::next(
            begin,
            index
        );
        return *left_it >= border ? left_it : MaxIt(
            left_it,
            mid
        );
            
    }
    else if (*mid < border) { // go right
        const set<int> tmp(mid, end);

        const auto return_it = FindNearestElement_(tmp, border);
        const auto return_begin = tmp.begin();
        const size_t index = std::distance(return_begin, return_it);

        const auto right_it = std::next(
            mid,
            index
        );
        return *right_it <= border ? right_it : MinIt(
            right_it,
            mid
        );
    }
    else {
        return end;
    }
}

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    if (numbers.empty()) {
        return numbers.end();
    }
    // set = { 1, 4, 6}
    // border =   0 3 5 6 100
    // lower_it = 1 4 6 6 3
    // correct =  1 4 4 6 6
    auto lower_it = numbers.lower_bound(border);
    //size_t dist_left = std::distance(numbers.begin(), lower_it);
    if (lower_it == numbers.end()) {
        lower_it = std::prev(lower_it);
    }

    if (*lower_it != border) {
        if (lower_it == numbers.begin()) {
            return lower_it;
        }
        auto prev_it = std::prev(lower_it);
        if (border - *prev_it > *lower_it-border) {
            return lower_it;
        }
        else {
            return prev_it;
        }
    }
    else {
        return lower_it;
    }
}

/*

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    // set<int>::const_iterator — тип итераторов для константного множества целых чисел
    //return FindNearestElement(numbers.begin(), numbers.end(), border);
    auto MaxIt = [](const auto& left, const auto& right) {
        return *left > *right ? left : right;
    };
    auto MinIt = [](const auto& left, const auto& right) {
        return *left < *right ? left : right;
    };    
    const auto begin = numbers.begin();
    const auto end = numbers.end();
    if (begin == end) { // container is empty returning end
        return end;
    }
    std::size_t size = std::distance(begin, end); // size of container between iterators
    if (size == 1) { // returning element if there is only one element
        return begin;
    }
    const auto mid = std::next(begin, size / 2);
    if (*mid == border) { // found at middle position
        return mid;   
    }
    else if (*mid > border) { // go left recursively
        const set<int> tmp(begin, mid);

        const auto return_it = FindNearestElement(tmp, border);
        const auto return_begin = tmp.begin();
        const size_t index = std::distance(return_begin, return_it);
        
        const auto left_it = std::next(
            begin,
            index
        );
        return *left_it >= border ? left_it : MaxIt(
            left_it,
            mid
        );
            
    }
    else if (*mid < border) { // go right
        const set<int> tmp(mid, end);

        const auto return_it = FindNearestElement(tmp, border);
        const auto return_begin = tmp.begin();
        const size_t index = std::distance(return_begin, return_it);

        const auto right_it = std::next(
            mid,
            index
        );
        return *right_it <= border ? right_it : MinIt(
            right_it,
            mid
        );
    }
    else {
        return end;
    }
}

*/

int main() {
    std::cout << std::endl << std::endl;
    
    set<int> numbers = { };
    cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " " << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100)  << endl;
    set<int> empty_set;
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    
    return 0;
}