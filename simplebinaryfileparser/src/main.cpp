#include "record_parser.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<std::uint8_t> bytes;
  bytes = make_sample_records();

  const auto result = parse_records(bytes);
  if (!result.ok()) {
    std::cerr << result.error << "\n";
    return 1;
  }
  for (const auto &record : result.records) {
    std::cout << record.id << " " << record.balance << " " << record.name
              << "\n";
  }
  return 0;
}
