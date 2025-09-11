#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <utility>
#include "Logger.hpp"

namespace mtl
{
    template <typename T>
    class vector
    {
    public:
        vector() = default;

        ~vector() = default;

        void reserve(size_t new_cap)
        {
            LOG("[DEBUG] [mtl::vector::reserve] Reserving new capacity: %llu \n", new_cap);
            if (new_cap > capacity())
            {
                grow(new_cap);
            }
        }

        void push_back(const T& value)
        {
            LOG("[DEBUG] [mtl::vector::push_back] Pushing back element \n");
            ensure_capacity();

            begin[size()] = std::move(value);
            ++end;
        }

        template <typename ...Args>
        T& emplace_back(Args&&... args)
        {
            ensure_capacity();
            T* place = begin + size();
            new (place) T(std::forward<Args>(args)...);
            ++end;
            return *place;
        }

        void pop_back()
        {
            if (size() != 0)
            {
                begin[size()].~T();
                --end;
            }
            LOG("[DEBUG] [mtl::vector::pop_back] After pop_back size: %llu , capacity: %llu \n", size(), capacity());
        }

        bool empty()
        {
            return size() == 0;
        }

        size_t size()
        {
            if (end == nullptr || begin == nullptr)
            {
                return 0;
            }
            return end - begin;
        }

        size_t capacity()
        {
            return end_cap - begin;
        }

        T& operator[](int index)
        {
            return begin[index];
        }

        T& at(int index)
        {
            if (index >= size())
            {
                throw std::out_of_range("No element at requested index");
            }

            return operator[](index);
        }
    private:
        T* begin = nullptr;
        T* end = nullptr;
        T* end_cap = nullptr;

        void ensure_capacity()
        {
            if (begin == nullptr)
            {
                grow(2);
            } else if (end == end_cap)
            {
                grow(capacity() * 2);
            }
        }

        void grow(size_t new_cap)
        {
            LOG("[DEBUG] [mtl::vector::grow] Growing with new capacity: %llu \n", new_cap);
            T* newBlock = new T[new_cap];
            size_t old_size = size();

            for (int i = 0; i < size(); i++)
            {
                newBlock[i] = std::move(begin[i]);
            }

            delete[] begin;

            begin = newBlock;
            end = begin + old_size;
            end_cap = begin + new_cap;
        }
    };
}

#endif //VECTOR_HPP
