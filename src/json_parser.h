#ifndef JSON_PARSER
#define JSON_PARSER

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <utility>

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

inline InfoBlock Parse(std::ifstream& json_file) {
  InfoBlock block{};
  std::string line{};
  while (std::getline(json_file, line)) {
    if (line.find("sensor") != std::string::npos) {
    if (line.find("Gyroscope") != std::string::npos) {
      block.device = "Gyroscope";
    } else if (line.find("Magnetometer") != std::string::npos) {
      block.device = "Magnetometer";
    } else if (line.find("Pedometer") != std::string::npos) {
      block.device = "Pedometer";
    } else if (line.find("Location") != std::string::npos) {
      block.device = "Location";
    }
    } else if (line.find("seconds_elapsed") != std::string::npos) {
      line = line.substr(line.find_first_of(integral));
      block.time = std::stold(line);
    } else if (line.find("\"x\"") != std::string::npos) {
      line = line.substr(line.find_first_of(integral));
      block.x = std::stold(line);
    } else if (line.find("\"y\"") != std::string::npos) {
      line = line.substr(line.find_first_of(integral));
      block.y = std::stold(line);
    } else if (line.find("\"z\"") != std::string::npos) {
      line = line.substr(line.find_first_of(integral));
      block.z = std::stold(line);
    } else if (line.find("steps") != std::string::npos) {
      line = line.substr(line.find_first_of(integral));
      block.steps = std::stoi(line);
    } else if (line.find("longitude") != std::string::npos) {
      line = line.substr(line.find_first_of(integral));
      block.coords.second = std::stold(line);
    } else if (line.find("latitude") != std::string::npos) {
      line = line.substr(line.find_first_of(integral));
      block.coords.first = std::stold(line);
    } else if (line.find("}") != std::string::npos) {
      return block;
    }
  }
  return block;
}

#endif
