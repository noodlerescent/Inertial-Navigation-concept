#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include "json_parser.h"

using ld_vector = std::vector<long double>;
using i_vector = std::vector<int64_t>;

struct Sensor {
  std::string name_{};
  ld_vector x_{};
  ld_vector y_{};
  ld_vector z_{};
  ld_vector time_{};
  i_vector steps_{};
  std::vector<std::pair<long double, long double>> coords_{};

  Sensor() = default;
  explicit Sensor(std::string name);
  void Get(InfoBlock& block);
  ~Sensor() = default;
};

Sensor::Sensor(std::string name) {
  name_ = name;
}

void Sensor::Get(InfoBlock& block) {
  time_.push_back(block.time);
  if (name_ == "Gyroscope" || name_ == "Magnetometer") {
    x_.push_back(block.x);
    y_.push_back(block.y);
    z_.push_back(block.z);
  } else if (name_ == "Pedometer") {
    steps_.push_back(block.steps);
  } else if (name_ == "Location") {
    coords_.push_back(block.coords);
  }
}

int main() {
  std::string name{};

  Sensor Gyroscope(std::string("Gyroscope")), Pedometer(std::string("Pedometer")),
         Magnetometer(std::string("Magnetometer")), Location(std::string("Location"));
  std::ifstream data("data1.json");
  while (data.peek() != EOF) {
    InfoBlock block = Parse(data);
    if (block.device == std::string("Gyroscope")) {
      Gyroscope.Get(block);
    } else if (block.device == std::string("Pedometer")) {
      Pedometer.Get(block);
    } else if (block.device == std::string("Magnetometer")) {
      Magnetometer.Get(block);
    } else if (block.device == std::string("Location")) {
      Location.Get(block);
    }
  }
  data.close();
  
  return 0;
}
