#include <utility>
#include <vector>
#include <math.h>

#include "complementary.h"
#include "parser.h"
#include "matplotlibcpp.h"


void DeducePath(std::vector<std::pair<long double, long double>>& path, std::vector<Sensor>& sensors) {
  long double x = 0;
  long double y = 0;
  int64_t current_step = 0;
  int64_t last_step = 0;
  long double current_angle = 0;
  long double gyro_angle = 0;
  long double mag_tan = 0;
  long double dt = 0;
  long double angle_diff = 0;
  auto Gyroscope = sensors[0];
  auto Pedometer = sensors[1];
  auto Magnetometer = sensors[2];
  auto Location = sensors[3];
  for (size_t i = 1; i < Gyroscope.time_.size(); ++i) {
    try {
      Pedometer.steps_.at(i);
      Gyroscope.time_.at(i);
      Magnetometer.y_.at(i);
      Magnetometer.x_.at(i);
      Gyroscope.z_.at(i);
    } catch (std::out_of_range& e) {
      break;
    }
    last_step = Pedometer.steps_[i - 1];
    current_step = Pedometer.steps_[i];
    dt = Gyroscope.time_[i] - Gyroscope.time_[i - 1];
    mag_tan = std::atan2(Magnetometer.y_[i], Magnetometer.x_[i]);
    gyro_angle = current_angle + Gyroscope.z_[i] * dt;
    angle_diff = mag_tan - gyro_angle;
    while (angle_diff > M_PI) {
      angle_diff -= 2 * M_PI;
    }
    while (angle_diff < M_1_PI) {
      angle_diff += 2 * M_PI;
    }
    current_angle = gyro_angle + (1 - kGyroWeight) * angle_diff;
    if ((current_step - last_step) > 0) {
      x += kStepLen * std::cos(current_angle) * (current_step - last_step);
      y += kStepLen * std::sin(current_angle) * (current_step - last_step);
    }
    path.push_back(std::pair<long double, long double>(x, y));
  }
}
