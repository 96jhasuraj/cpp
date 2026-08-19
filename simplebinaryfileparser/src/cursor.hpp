#pragma once
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>

class Cursor {
public:
  Cursor(std::span<const std::uint8_t> bytes) : bytes(bytes), offset(0) {}
  bool read_u8(std::uint8_t &value) {
    if (!can_read(1)) {
      return false;
    }
    value = bytes[offset++];
    // std::cout << offset << " \n";
    return true;
  }
  bool read_u16_le(std::uint16_t &value) {
    if (!can_read(2)) {
      return false;
    }
    value = static_cast<std::uint16_t>(bytes[offset]) |
            static_cast<std::uint16_t>(bytes[offset + 1] << 8);
    offset += 2;
    // std::cout << offset << " \n";
    return true;
  }
  bool read_u32_le(std::uint32_t &value) {
    if (!can_read(4)) {
      return false;
    }
    value = static_cast<std::uint32_t>(bytes[offset]) |
            static_cast<std::uint32_t>(bytes[offset + 1] << 8) |
            static_cast<std::uint32_t>(bytes[offset + 2] << 16) |
            static_cast<std::uint32_t>(bytes[offset + 3] << 24);

    offset += 4;
    // std::cout << offset << " \n";
    return true;
  }
  bool read_u64_le(std::uint64_t &value) {
    if (!can_read(4)) {
      return false;
    }
    value = static_cast<std::uint64_t>(bytes[offset++]);
    for (std::size_t i = 1; i < 8; i++) {
      value |= (static_cast<std::uint64_t>(bytes[offset++] << i * 8));
    }
    // std::cout << offset << " \n";
    return true;
  }
  bool read_string(std::size_t size, std::string &str) {
    if (!can_read(size)) {
      return false;
    }
    const auto *start = reinterpret_cast<const char *>(bytes.data() + offset);
    str.assign(start, size);
    offset += size;
    // std::cout << offset << " \n";
    return true;
  }

private:
  std::span<const std::uint8_t> bytes;
  std::size_t offset;
  bool can_read(std::size_t count) const {
    return offset <= bytes.size() && count <= bytes.size() - offset;
  }
};
