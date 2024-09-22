// OrderPool.hpp

#ifndef FASTLOB_ORDERPOOL_H
#define FASTLOB_ORDERPOOL_H

#include <vector>
#include <cstdint>
#include <type_traits>
#include "Order.h"
#include "utility.h"

/**
 * @brief A template class for managing a pool of orders.
 *
 * This class is designed to efficiently manage a collection of orders, allowing for
 * the allocation and deallocation of order objects. It uses a vector to store allocated
 * orders and another vector to keep track of freed orders for reuse. This approach helps
 * in reducing the overhead of frequently creating and destroying order objects.
 *
 * @tparam T The type of the order object.
 * @tparam SizeType The type used for sizing and indexing the pool.
 * @tparam PtrType The type used for pointers to the order objects.
 */
template <class T, typename SizeType, typename PtrType>
class OrderPool {
public:
    using ptr_t = PtrType; ///< Type for pointers to order objects.
    using size_type = SizeType; ///< Type for sizing and indexing the pool.

    /**
     * @brief Constructs a new Order Pool object.
     *
     * Initializes the pool with no allocated or free orders, reserving initial
     * capacity as needed.
     */
    OrderPool();

    /**
     * @brief Allocates an order object from the pool.
     *
     * If there are no free orders available, a new order is created and added to the pool.
     * Otherwise, a previously deallocated order is reused.
     *
     * @return OrderIDType A pointer to the allocated order object.
     */
    PtrType allocate();

    /**
     * @brief Deallocates an order object, returning it to the pool.
     *
     * The deallocated order is added to the list of free orders for reuse.
     *
     * @param ptr A pointer to the order object to be deallocated.
     */
    void deallocate(OrderIDType ptr);

    /**
     * @brief Retrieves an order object from the pool by its index.
     *
     * This function provides access to an order object based on its index in the
     * allocated vector. It is useful for iterating over all allocated orders.
     *
     * @param index The index of the order object in the pool.
     * @return T* A pointer to the order object at the specified index.
     */
    T* get(size_type index);

    /**
     * @brief Gets the current size of the pool.
     *
     * This includes both allocated and deallocated (free) orders.
     *
     * @return size_type The total number of orders currently managed by the pool.
     */
    size_type size() const;

private:
    std::vector<T> m_allocated; ///< Vector of allocated orders.
    std::vector<ptr_t> m_free; ///< Vector of pointers to deallocated (free) orders.
};

#endif FASTLOB_ORDERPOOL_H