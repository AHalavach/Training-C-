#pragma once

#include <iostream>
#include <utility>
#include <algorithm>

template< typename T >
class Vector;

template< typename T >
std::ostream& operator<< (std::ostream& out, const Vector<T>& vec);


template< typename T >
class Vector
{
    size_t size_index;
    size_t vector_capacity;
    T* memory_block;

    void swap(Vector& lhs, Vector& rhs) noexcept
    {
        std::swap(lhs.size_index, rhs.size_index);
        std::swap(lhs.vector_capacity, rhs.vector_capacity);
        std::swap(lhs.memory_block, rhs.memory_block);

    }

    void allocate_mem(size_t mem_size)
    {
        if (memory_block)
            delete[] memory_block;
        
        memory_block = new T[mem_size];
    }

    friend std::ostream& operator<< <>(std::ostream& out, const Vector& vec);

public:
    struct iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;  
        using reference = T&; 

        explicit iterator(pointer ptr) : m_ptr(ptr) {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        // Prefix increment
        iterator& operator++() { ++m_ptr; return *this; }

        // Postfix increment
        iterator operator++(int) { iterator tmp = *this; ++m_ptr; return tmp; }

        // Prefix decrement
        iterator& operator--() { --m_ptr; return *this; }

        // Postfix decrement
        iterator operator--(int) { iterator tmp = *this; --m_ptr; return tmp; }

        friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };
        friend size_t operator- (const iterator& a, const iterator& b) { return a.m_ptr - b.m_ptr; };
        friend bool operator< (const iterator& a, const iterator& b) { return a.m_ptr < b.m_ptr; };

    private:
        pointer m_ptr;
    };

    struct const_iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;  // or also value_type*
        using reference = const T&;  // or also value_type& 

        explicit const_iterator(pointer ptr) : m_ptr(ptr) {}
        const_iterator(const iterator& it) : m_ptr(it.m_ptr) {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        // Prefix increment
        const_iterator& operator++() { m_ptr++; return *this; }

        // Postfix increment
        const_iterator operator++(int) { const_iterator tmp = *this; ++m_ptr; return tmp; }

        // Prefix decrement
        const_iterator& operator--() { m_ptr--; return *this; }

        // Postfix decrement
        const_iterator operator--(int) { const_iterator tmp = *this; --m_ptr; return tmp; }

        friend bool operator== (const const_iterator& a, const const_iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const const_iterator& a, const const_iterator& b) { return a.m_ptr != b.m_ptr; };
        friend size_t operator- (const const_iterator& a, const const_iterator& b) { return a.m_ptr - b.m_ptr; };

    private:
        pointer m_ptr;
    };

    Vector() : 
        size_index{ 0 },
        vector_capacity{ 0 },
        memory_block{ nullptr }
    {
        std::cout << "Constr: default \r\n";
    }

    Vector(size_t sz) : 
        size_index{ sz },
        vector_capacity{ sz },
        memory_block{ new T[size_index] }
    {
        std::cout << "Constr: size \r\n";
    }

    Vector(size_t sz, const T val) : Vector(sz)
    {
        for (size_t i = 0; i < size_index; i++) 
        {
            memory_block[i] = val;
        }

        std::cout << "Constr: size + init value \r\n";
    }

    Vector(std::initializer_list<T> list) : Vector(list.size())
    {
        std::size_t index = 0;
           for (const auto& item : list)
            memory_block[index++] = item;

        std::cout << "Constr: init list \r\n";
    }

    Vector(const Vector& vec) 
    {
        if (vector_capacity < vec.vector_capacity)
        {
            allocate_mem(vec.vector_capacity);
        }
        vector_capacity = vec.vector_capacity;
        size_index = vec.size_index;
        std::copy(vec.memory_block, vec.memory_block + size_index, memory_block);

        std::cout << "Constr: copy \r\n";
    }

    Vector& operator=(const Vector& vec)
    {
        if (&vec == this)
            return *this;

        if (vector_capacity < vec.vector_capacity)
        {
            allocate_mem(vec.vector_capacity);
        }
         
        vector_capacity = vec.vector_capacity;
        size_index = vec.size_index;

        for (std::size_t i = 0; i < vec.size_index; i++)
            memory_block[i] = vec.memory_block[i];

        std::cout << "operator=: copy \r\n";

       return *this;
    }

    Vector(Vector&& vec) noexcept
    { 
        swap(*this, vec); 

        std::cout << "Constr: move \r\n";
    }

    Vector& operator=(Vector&& vec)
    {
        if (&vec == this)
            return *this;

        swap(*this, vec);

        std::cout << "operator=: move \r\n";

        return *this;
    }

    ~Vector()
    {
        if (memory_block)
            delete[] memory_block;

        std::cout << "Destr \r\n";
    }

    /* modifiers */
    void push_back(const T& val)
    {
        if (size_index >= vector_capacity) {
            Vector<T>  temp(vector_capacity * 2);
            
            for (size_t i = 0; i < this->size_index; i++)
            {
                temp[i] = memory_block[i];
            }

            *this = std::move(temp);
        }

        memory_block[size_index++] = val;
    }

    void pop_back() 
    { 
        --size_index; 
    }

    void erase(int index)
    {
        for (int temp_index = index; temp_index < size_index; ++temp_index)
        {
            /* Move elements one step back until we get to the desired location */
            memory_block[temp_index] = memory_block[temp_index + 1];
        }
        --size_index;

    }
    
    void clear()
    {
        delete[] memory_block;
        memory_block = nullptr;
        size_index = 0;
    }

    const T& front() const { return memory_block[0]; }
    const T& back() const { return memory_block[size_index - 1]; }
    T& front() { return memory_block[0]; }
    T& back() { return memory_block[size_index - 1]; }

    const T& operator[](const int i) const 
    { 
        return memory_block[i]; 
    }

    T& operator[](const int i) 
    {
        return memory_block[i]; 
    }

    std::size_t capacity() const
    { 
        return vector_capacity; 
    }

    std::size_t size() const 
    { 
        return size_index; 
    }

    bool empty() const 
    { 
        return (size_index == 0); 
    }

    iterator begin() noexcept { return iterator(memory_block); }
    iterator end() noexcept { return iterator(memory_block + size_index); }
    const_iterator cbegin() const noexcept { return const_iterator(memory_block); }
    const_iterator cend() const noexcept { return const_iterator(memory_block + size_index); }
};

template< typename T >
std::ostream& operator<< (std::ostream& out, const Vector<T>& vec)
{
    for (size_t i = 0; i < vec.size_index; i++)
    {
        std::cout << i << " : " << vec.memory_block[i] << std::endl;
    }

    return out;
}

