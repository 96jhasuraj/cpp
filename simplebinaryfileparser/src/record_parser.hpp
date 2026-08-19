#pragma once
#include "cursor.hpp"
#include "utility.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>

struct Record {
  std::uint32_t id = 0;
  std::uint64_t balance = 0;
  std::string name;
};

struct ParseResult {
  std::vector<Record> records;
  std::string error;
  bool ok() const { return error.empty(); }
};

ParseResult parse_records(std::span<const std::uint8_t> bytes) {
  Cursor cursor(bytes);

  for (const auto expected : std::string_view("BANK")) {
    std::uint8_t actual = 0;
    if (!cursor.read_u8(actual) ||
        actual != static_cast<std::uint8_t>(expected)) {
      return {{}, "invalid header"};
    }
  }

  std::uint32_t count = 0;
  if (!cursor.read_u32_le(count)) {
    return {{}, "missing record count"};
  }

  std::vector<Record> records;

  for (std::uint32_t i = 0; i < count; i++) {
    // std::cout << i << "th record out of " << count << "records \n";
    Record record;
    std::uint16_t name_len = 0;
    if (!cursor.read_u32_le(record.id)) {
      return {{}, "missing record id"};
    }
    if (!cursor.read_u64_le(record.balance)) {
      return {{}, "missing money in account"};
    }
    if (!cursor.read_u16_le(name_len)) {
      return {{}, "missing name length"};
    }
    if (!cursor.read_string(name_len, record.name)) {
      return {{}, "missing name of holder"};
    }

    records.push_back(std::move(record));
  }

  return {std::move(records), ""};
}
