#include "parser.h"

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

InfoBlock Parse(std::ifstream& json_file) {
  InfoBlock block{};
  std::string line{};
  while (std::getline(json_file, line)) {
    if (line.find("Uncalibrated") != std::string::npos) {
      while(line.find("}") == std::string::npos) {
        std::getline(json_file, line);
      }
      continue;
    }
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

void GetParsedData(std::vector<Sensor>& sensors) {
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
  sensors.reserve(4);
  sensors.push_back(Gyroscope);
  sensors.push_back(Pedometer);
  sensors.push_back(Magnetometer);
  sensors.push_back(Location);
}
