//
// Created by viraj on 20/06/24.
//

#include "OrderPool.h"

// Constructor implementation
template <class T, typename SizeType, typename PtrType>
OrderPool<T, SizeType, PtrType>::OrderPool() {
    m_allocated.reserve(1000); // Pre-allocate space to improve efficiency
    m_free.reserve(1000); // Pre-allocate space for the free list
}

// Allocate an order from the pool
template <class T, typename SizeType, typename PtrType>

PtrType OrderPool<T, SizeType, PtrType>::allocate() {
    if (m_free.empty()) { // If no free orders, create a new one
        m_allocated.push_back(T());
        return static_cast<PtrType>(m_allocated.size() - 1); // Return the index of the newly created order
    } else { // Reuse a free order
        auto ret = m_free.back();
        m_free.pop_back(); // Remove from free list
        return ret; // Return the index of the reused order
    }
}

// Deallocate an order, returning it to the pool
template <class T, typename SizeType, typename PtrType>
void OrderPool<T, SizeType, PtrType>::deallocate(OrderIDType ptr) {
    m_free.push_back(ptr); // Add the order back to the free list
}

// Retrieve an order from the pool by index
template <class T, typename SizeType, typename PtrType>
T* OrderPool<T, SizeType, PtrType>::get(size_type index) {
    return &m_allocated[static_cast<uint32_t>(index)]; // Return the order at the specified index
}

// Get the current size of the pool
template <class T, typename SizeType, typename PtrType>
typename OrderPool<T, SizeType, PtrType>::size_type OrderPool<T, SizeType, PtrType>::size() const {
    return static_cast<size_type>(m_allocated.size()); // Return the size of the allocated list
}

// Explicit template instantiation
template class OrderPool<Order, uint32_t, OrderIDType>;