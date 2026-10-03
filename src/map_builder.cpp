#include <iostream>
#include <vector>

#include "parser.h"
#include "complementary.h"

int main() {
  std::vector<std::pair<long double, long double>> path{};
  std::vector<Sensor> sensors{};
  GetParsedData(sensors);
  DeducePath(path, sensors);
  for (size_t i = 0; i < path.size(); ++i) {
    std::cout << "x: " << path[i].first << " y: " << path[i].second << '\n';
  }
  return 0;
}
