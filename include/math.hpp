#ifndef MATH_HPP
#define MATH_HPP

#include "logger.hpp"

namespace mtl
{
    template <typename T>
    class vec2d
    {
    public:
        T x = 0.0f;
        T y = 0.0f;
        vec2d() = default;
        explicit vec2d(T x) : x(x), y(x)
        {
            LOG("[DEBUG] [mtl::vec2d::constructor]\n");
        }

        vec2d(T x, T y) : x(x), y(y)
        {
            LOG("[DEBUG] [mtl::vec2d::constructor]\n");
        }

        ~vec2d()
        {
            LOG("[DEBUG] [mtl::vec2d::destructor]\n");
        }

        vec2d(vec2d& other) : x(other.x), y(other.y)
        {
            LOG("[DEBUG] [mtl::vec2d::copy_constructor]\n");
        }

        vec2d(vec2d&& other)  noexcept : x(other.x), y(other.y)
        {
            LOG("[DEBUG] [mtl::vec2d::move_constructor]\n");
        }

        vec2d& operator=(const vec2d& other)
        {
            if (this != &other)
            {
                x = other.x;
                y = other.y;
                LOG("[DEBUG] [mtl::vec2d::copy_assignment]\n");
            }

            return *this;
        }

        vec2d& operator=(vec2d&& other) noexcept
        {
            if (this != &other)
            {
                x = other.x;
                y = other.y;
                LOG("[DEBUG] [mtl::vec2d::move_assignment]\n");
            }
            return *this;
        }
    };
}


#endif //MATH_HPP
