#include <iostream>
#include <vector>
#include <algorithm>
//#include <ranges>

#include "lib/ranges.h"
#include "lib/adapters.h"


// template <typename T>
// struct lol;


// void copy_test() {
//     std::vector<int> a = {1, 2, 3}, b = {0, 0, 0};

//     for (auto i : LazyCopyAdapter(a.begin(), a.end(), b.begin())) {
//         std::cout << i << " ";
//     } std::cout << '\n';

//     for (auto& i : b) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }

// void transform_test() {
//     std::vector<int> a = {1, 2, 3}, b = {0, 0, 0};

//     for (auto i : LazyTransformAdapter(a.begin(), a.end(), [](int a){return a * 10;})) {
//         std::cout << i << " ";
//     } std::cout << '\n';

//     for (auto& i : a) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }

// void reverse_test() {
//     std::vector<int> a = {1, 2, 3}, b = {0, 0, 0};

//     for (auto i : LazyReverseAdapter(a.begin(), a.end())) {
//         std::cout << i << " ";
//     } std::cout << '\n';

//     for (auto& i : b) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }

// void keys_test() {
//     std::vector<std::pair<int, int>> a = {{1, 2}, {3, 4}, {5, 6}};

//     for (auto i : LazyKeysAdapter(a.begin(), a.end())) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }

// void values_test() {
//     std::vector<std::pair<int, int>> a = {{1, 2}, {3, 4}, {5, 6}};

//     for (auto i : LazyValuesAdapter(a.begin(), a.end())) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }

// void filter_test() {
//     std::vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//     for (auto i : LazyFilterAdapter(a.begin(), a.end(), [](int a){return a % 2 == 1;})) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }

// void take_test() {
//     std::vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//     for (auto i : LazyTakeAdapter(a.begin(), a.end(), 5)) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }

// void drop_test() {
//     std::vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//     for (auto i : LazyDropAdapter(a.begin(), a.end(), 1)) {
//         std::cout << i << " ";
//     } std::cout << '\n';
//     std::cout << '\n';
// }


int main() {
    // std::size_t a;

    // copy_test(); /// ok

    // transform_test(); /// ok

    // reverse_test(); /// ok

    // keys_test(); /// ok

    // values_test(); /// ok

    // filter_test(); /// ok

    // take_test(); /// ok

    // drop_test(); /// ok

    
}