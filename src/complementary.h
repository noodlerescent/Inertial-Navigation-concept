#ifndef COMPLEMENTARY_H
#define COMPLEMENTARY_H

#include "parser.h"

const long double kGyroWeight = 0.98;
const long double kStepLen = 0.75;

void DeducePath(std::vector<std::pair<long double, long double>>& path, std::vector<Sensor>& sensors);
#endif
