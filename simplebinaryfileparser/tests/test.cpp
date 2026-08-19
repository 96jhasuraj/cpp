#include "record_parser.hpp"
#include < iostream>
#include <cstdint>
#include <string>
#include <vector>

int require(bool condition, const char *message) {
  if (!condition) {
    std::cout << message << "\n";
    return 1;
  }
  return 0;
}

int main() {
  const auto sample = make_sample_records();
  const auto parse = parse_records(sample);
  if (const auto code =
          require(parse.ok(), "expected sample parse to succeed")) {
    return code;
  }
  if (const auto code = require(parse.records.size() == 2,
                                "expected sample parse size to be 2")) {
    return code;
  }
  if (const auto code =
          require(parse.records[0].id == 1, "expected 0th sample id as 1")) {
    return code;
  }
  if (const auto code = require(parse.records[0].name == "SURAJ",
                                "expected 0th sample name as Suraj")) {
    return code;
  }

  std::vector<std::uint8_t> bad{'B', 'A', 'N', 'K'};
  append_u32_le(bad, 1);
  append_u32_le(bad, 99);
  append_u16_le(bad, 4);
  bad.push_back('S');
  const auto badparse = parse_records(bad);
  if (const auto code =
          require(!badparse.ok(), "expected sparsing fail due to truncation")) {
    return code;
  }
}
