#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <utility>
#include "logger.hpp"

namespace mtl
{
    template <typename T>
    class vector
    {
    public:
        class iterator
        {
        public:
            explicit iterator(T* p): m_p(p) {}

            T& operator*()
            {
                return *m_p;
            }

            T* operator->()
            {
                return m_p;
            }

            iterator& operator++()
            {
                ++m_p;
                return *this;
            }

            iterator& operator--()
            {
                --m_p;
                return *this;
            }

            iterator operator++(int)
            {
                iterator old_value = *this;
                operator++();
                return old_value;
            }

            iterator operator--(int)
            {
                iterator old_value = *this;
                operator--();
                return old_value;
            }

            iterator operator+(int num)
            {
                return iterator(m_p + num);
            }

            iterator operator-(int num)
            {
                return iterator(m_p - num);
            }

            bool operator==(const iterator& other) const
            {
                return m_p == other.m_p;
            }

            bool operator!=(const iterator& other) const
            {
                return m_p != other.m_p;
            }

        protected:
            T* m_p;
        };

        class reverse_iterator
        {
        public:
            explicit reverse_iterator(iterator& iter): m_iter(iter) {}

            reverse_iterator operator++(int)
            {
                reverse_iterator old_value = *this;
                operator++();
                return old_value;
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator old_value = *this;
                operator--();
                return old_value;
            }

            reverse_iterator& operator++()
            {
                m_iter.operator--();
                return *this;
            }

            reverse_iterator& operator--()
            {
                m_iter.operator++();
                return *this;
            }

            T& operator*()
            {
                return m_iter.operator*();
            }

            T* operator->()
            {
                return m_iter.operator->();
            }

            reverse_iterator operator+(int n)
            {
                m_iter.operator+(n);
                return *this;
            }

            reverse_iterator operator-(int n)
            {
                m_iter.operator-(n);
                return *this;
            }

            bool operator==(const reverse_iterator& other) const
            {
                return m_iter.operator==(other.m_iter);
            }

            bool operator==(const iterator& other) const
            {
                return m_iter.operator==(other);
            }

            bool operator!=(const reverse_iterator& other) const
            {
                return m_iter.operator!=(other.m_iter);
            }

            bool operator!=(const iterator& other) const
            {
                return m_iter.operator!=(other);
            }
        protected:
            iterator m_iter;
        };

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

            m_begin[end_index()] = std::move(value);
            ++m_end;
        }

        template <typename ...Args>
        T& emplace_back(Args&&... args)
        {
            ensure_capacity();
            T* place = m_begin + size();
            new (place) T(std::forward<Args>(args)...);
            ++m_end;
            return *place;
        }

        void pop_back()
        {
            if (size() != 0)
            {
                m_end->~T();
                --m_end;
            }
            LOG("[DEBUG] [mtl::vector::pop_back] After pop_back size: %llu , capacity: %llu \n", size(), capacity());
        }

        bool empty()
        {
            return size() == 0;
        }

        size_t size()
        {
            if (m_end == nullptr || m_begin == nullptr)
            {
                return 0;
            }
            return m_end - m_begin;
        }

        size_t capacity()
        {
            return m_endCap - m_begin;
        }

        T& operator[](int index)
        {
            return m_begin[index];
        }

        T& at(int index)
        {
            if (index >= size())
            {
                throw std::out_of_range("No element at requested index");
            }

            return operator[](index);
        }

        iterator begin()
        {
            return iterator(m_begin);
        }

        iterator end()
        {
            return iterator(m_end);
        }

        reverse_iterator rbegin()
        {
            iterator iter(m_end - 1);
            reverse_iterator r_i(iter);
            return r_i;
        }

        reverse_iterator rend()
        {
            iterator iter(m_begin - 1);
            reverse_iterator r_i(iter);
            return r_i;
        }
    private:
        T* m_begin = nullptr;
        T* m_end = nullptr;
        T* m_endCap = nullptr;

        size_t end_index()
        {
            if (m_end == nullptr || m_begin == nullptr)
            {
                return 0;
            }
            if (m_end - m_begin < 0)
            {
                return 0;
            }
            return m_end - m_begin;
        }

        void ensure_capacity()
        {
            if (m_begin == nullptr)
            {
                grow(2);
            } else if (m_end == m_endCap)
            {
                grow(capacity() * 2);
            }
        }

        void grow(size_t new_cap)
        {
            LOG("[DEBUG] [mtl::vector::grow] Growing with new capacity: %llu \n", new_cap);
            T* newBlock = new T[new_cap];
            size_t old_end_index = end_index();

            for (int i = 0; i < size(); i++)
            {
                newBlock[i] = std::move(m_begin[i]);
            }

            delete[] m_begin;

            m_begin = newBlock;
            m_end = m_begin + old_end_index;
            m_endCap = m_begin + new_cap;
        }
    };
}

#endif //VECTOR_HPP
