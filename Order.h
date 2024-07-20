//
// Created by viraj on 18/06/24.
//

#ifndef FASTLOB_ORDER_H
#define FASTLOB_ORDER_H

#include "utility.h"
#include <type_traits>

typedef struct Order {
    OrderIDType order_id;
    VolumeType volume;
    PriceType price;
    bool isBuy;

    struct Order* prev;
    struct Order* next;

} Order;

class PriceLevel {
public:
    PriceLevel() = default;
    PriceLevel(PriceType _price, LevelType _ptr)
    : m_price(_price), m_ptr(_ptr) {}
    PriceType m_price;
    LevelType m_ptr;

    bool operator<(const PriceLevel& other) const {
        return m_price < other.m_price;
    }
};




#endif //FASTLOB_ORDER_H
