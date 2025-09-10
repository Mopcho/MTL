#include <iostream>

#include "include/math.hpp"
#include "include/Vector.hpp"

int main()
{
    mtl::vector<mtl::vec2d<float>> arr;
    arr.push_back(mtl::vec2d{5.0f, 5.0f});
    arr.pop_back();

    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i].x << " " <<  arr[i].y << std::endl;
    }
    return 0;
}
