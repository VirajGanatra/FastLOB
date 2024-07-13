//
// Created by viraj on 13/07/24.
//

#ifndef FASTLOB_TYPES_H
#define FASTLOB_TYPES_H

#include <cstdint>
#include <type_traits>

// Define custom pointer types to save space and preserve addresses
enum class BookIDType : uint16_t {};
enum class OrderIDType : uint32_t {};
enum class LevelType : uint32_t {};

// Define custom types for prices and volumes
enum class PriceType : int32_t {}; //
enum class VolumeType : uint32_t {};

// implement std:to_underlying for enum classes
template<typename Enum>
inline constexpr auto to_underlying(Enum e) noexcept -> typename std::underlying_type<Enum>::type {
    return static_cast<typename std::underlying_type<Enum>::type>(e);
}


#endif //FASTLOB_TYPES_H