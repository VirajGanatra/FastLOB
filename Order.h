//
// Created by viraj on 18/06/24.
//

#ifndef FASTLOB_ORDER_H
#define FASTLOB_ORDER_H

#include <cstdint>
#include <memory>

struct Order {
    uint64_t order_id;
    uint64_t price;
    uint64_t volume;

    std::unique_ptr<Order> prev;
    std::unique_ptr<Order> next;

    Order(uint64_t order_id, uint64_t price, uint64_t volume) : order_id(order_id), price(price), volume(volume), next(nullptr), prev(nullptr) {}
};
#endif //FASTLOB_ORDER_H
