//
// Created by viraj on 20/06/24.
//

//
// OrderPool.h
//
// This header file defines the OrderPool and level classes for managing orders in a trading system.
// It includes mechanisms for allocating, deallocating, and accessing orders efficiently.
//

#ifndef FASTLOB_ORDERPOOL_H
#define FASTLOB_ORDERPOOL_H

#include <vector>
#include <cstdint>
#include <type_traits>
#include "Order.h"
#include "utility.h"

/**
 * Template class for managing a pool of orders.
 *
 * @tparam T The type of the orders in the pool.
 * @tparam SizeType The type used for sizing and indexing the pool.
 * @tparam PtrType The pointer type used for order pointers.
 */
template <class T, typename SizeType, typename PtrType>
class OrderPool {
public:
    using ptr_t = PtrType; ///< Type alias for the pointer type.
    using size_type = SizeType; ///< Type alias for the size type.

    /**
     * Constructor for OrderPool.
     * Initializes the pool with reserved space for efficiency.
     */
    OrderPool() {
        m_allocated.reserve(1000);
        m_free.reserve(1000);
    }

    /**
     * Allocates an order from the pool.
     *
     * @return A pointer to the allocated order.
     */
    T* allocate() {
        if (m_free.empty()) {
            m_allocated.push_back(T());
            return &m_allocated.back();
        } else {
            T* ptr = m_free.back();
            m_free.pop_back();
            return ptr;
        }
    }

    /**
     * Deallocates an order, returning it to the pool.
     *
     * @param ptr Pointer to the order to deallocate.
     */
    void deallocate(T* ptr) {
        m_free.push_back(ptr);
    }

    /**
     * Retrieves an order from the pool by index.
     *
     * @param index The index of the order to retrieve.
     * @return A pointer to the order.
     */
    T* get(size_type index) {
        return &m_allocated[static_cast<uint32_t>(index)];
    }

    /**
     * Gets the current size of the pool.
     *
     * @return The size of the pool.
     */
    size_type size() const {
        return static_cast<size_type>(m_allocated.size());
    }

private:
    std::vector<T> m_allocated; ///< Vector of allocated orders.
    std::vector<ptr_t> m_free; ///< Vector of pointers to free orders.
};

/**
 * Class representing a level in an order book.
 */
class level {
public:
    uint64_t price; ///< Price level of the orders.
    OrderPool<Order, uint32_t, Order*> order_pool; ///< Pool of orders at this price level.

    /**
     * Constructor for a level.
     *
     * @param price The price of the level.
     */
    level(uint64_t price) : price(price) {}

    /**
     * Adds an order to the level.
     *
     * @param order_id The ID of the order.
     * @param volume The volume of the order.
     * @return A pointer to the added order.
     */
    Order* add_order(uint64_t order_id, uint64_t volume) {
        Order* order = order_pool.allocate();
        order->order_id = order_id;
        order->volume = volume;
        return order;
    }

    /**
     * Removes an order from the level.
     *
     * @param order Pointer to the order to remove.
     */
    void remove_order(Order* order) {
        order_pool.deallocate(order);
    }
};

#endif //FASTLOB_ORDERPOOL_H
