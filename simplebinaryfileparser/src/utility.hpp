#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

void append_i64_le(std::vector<std::uint8_t> &out, std::uint64_t value) {
  for (int shift = 0; shift < 64; shift += 8) {
    out.push_back(static_cast<std::uint8_t>((value >> shift) & 0xffu));
  }
}

void append_u32_le(std::vector<std::uint8_t> &out, std::uint32_t value) {
  for (int shift = 0; shift < 32; shift += 8) {
    out.push_back(static_cast<std::uint8_t>((value >> shift) & 0xffu));
  }
}
void append_u16_le(std::vector<std::uint8_t> &out, std::uint16_t value) {
  for (int shift = 0; shift < 16; shift += 8) {
    out.push_back(static_cast<std::uint8_t>((value >> shift) & 0xffu));
  }
}

std::vector<std::uint8_t> make_sample_records() {
  std::vector<std::uint8_t> bytes{'B', 'A', 'N', 'K'};
  append_u32_le(bytes, 2);

  append_u32_le(bytes, 1);
  append_i64_le(bytes, 2000);
  append_u16_le(bytes, 5);
  bytes.insert(bytes.end(), {'S', 'U', 'R', 'A', 'J'});

  append_u32_le(bytes, 2);
  append_i64_le(bytes, 10000);
  append_u16_le(bytes, 3);
  bytes.insert(bytes.end(), {'J', 'H', 'A'});
  return bytes;
}
