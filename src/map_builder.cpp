#include <iostream>
#include <vector>

#include "parser.h"
#include "complementary.h"
#include "matplotlibcpp.h"

int main() {
  std::vector<std::pair<long double, long double>> path{};
  std::vector<Sensor> sensors{};
  GetParsedData(sensors);
  DeducePath(path, sensors);
  std::vector<long double> x_path{};
  std::vector<long double> y_path{};
  for (size_t i = 0; i < path.size(); ++i) {
    x_path.push_back(path[i].first);
    y_path.push_back(path[i].second);
  }
  matplotlibcpp::plot(x_path, y_path, "r-");
  matplotlibcpp::title("Inertial map");
  matplotlibcpp::xlabel("X axis");
  matplotlibcpp::ylabel("Y axis");
  matplotlibcpp::show();
  return 0;
}
