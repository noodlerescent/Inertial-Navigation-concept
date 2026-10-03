#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using ld_vector = std::vector<long double>;
using i_vector = std::vector<int64_t>;

const std::string integral("-0123456789");

struct InfoBlock {
  std::string line{};
  std::string device{};
  long double x = 0;
  long double y = 0;
  long double z = 0;
  long double time = 0;
  std::pair<long double, long double> coords{};
  int64_t steps = 0;
};

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

InfoBlock Parse(std::ifstream& json_file);

void GetParsedData(std::vector<Sensor>& sensors);

#endif
