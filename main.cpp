#include <iostream>

#include "include/math.hpp"
#include "include/vector.hpp"

int main()
{
    mtl::vector<mtl::vec2d<float>> arr;
    arr.push_back(mtl::vec2d{5.0f, 5.0f}); // 0
    arr.push_back(mtl::vec2d{4.0f, 5.0f}); // 1
    arr.push_back(mtl::vec2d{3.0f, 5.0f}); // 2
    arr.push_back(mtl::vec2d{2.0f, 5.0f}); // 3
    arr.push_back(mtl::vec2d{1.0f, 5.0f}); // 4 X

    // mtl::vector<float> arr;
    // arr.push_back(5.0f);
    // arr.push_back(5.0f);
    // arr.push_back(5.0f);
    // arr.push_back(5.0f);
    // arr.push_back(5.0f);

    arr.pop_back();

    auto it = arr.rbegin();

    while (it != arr.rend())
    {
        std::cout << (*it).x << " " <<  it->y << std::endl;
        ++it;
    }

    // auto it = arr.begin();
    //
    // while (it != arr.end())
    // {
    //     std::cout << (*it).x << " " <<  it->y << std::endl;
    //     ++it;
    // }
    return 0;
}
