#include "D_Point.h"

#include <math.h>

D_Point::D_Point(double x, double y) : x_(x), y_(y) {}

double D_Point::Distance(D_Point p1, D_Point p2) {
  return sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2));
}
