#include "LinearFitting.h"

#include <assert.h>

bool LinearFitting::CurveFitting(const std::vector<D_Point> &src_points,
                                 std::vector<D_Point> &dst_points) {

  if (src_points.size() <= 2) {
    assert(false);
    return false;
  }
  for (size_t i = 0; i < src_points.size() - 2; i++) {
    std::vector<D_Point> fitting_points;
    fitting_points.push_back(src_points[i]);
    double trace_len = 0;
    for (size_t j = i; j < src_points.size() - 1; j++) {
      trace_len += D_Point::Distance(src_points[j], src_points[j + 1]);
      if (trace_len  > 2) {
        i = j + 1;
        break;
      }
      fitting_points.push_back(src_points[j + 1]);      
    }
    if (fitting_points.size() > 2) {
      double a0 = 0.;
      double a1 = 0.;
      CalculateCoefficient(fitting_points, a0, a1);
      // y = a0 + a1 * x;
      D_Point p1 = PointProjectionLine(fitting_points[0], a0, a1);
      D_Point p2 = PointProjectionLine(fitting_points[fitting_points.size() - 1], a0, a1);
      dst_points.push_back(p1);
      dst_points.push_back(p2);
    }  else {
      dst_points.insert(dst_points.end(), fitting_points.begin(), fitting_points.end());
    }
  }
  return true;
}

bool LinearFitting::CalculateCoefficient(const std::vector<D_Point> &points,
                                         double &a0, double &a1) {

  size_t point_num = points.size();
  if (point_num < 2) {
    return false;
  }
  double s1 = point_num;
  double s2 = 0.;
  double s3 = 0.;
  double s4 = 0.;
  double s5 = 0.;
  for (size_t i = 0; i < points.size(); i++) {
    s2 += points[i].x();
    s3 += points[i].x() * points[i].x();
    s4 += points[i].y();
    s5 += points[i].x() * points[i].y();
  }
  a1 = (s1 * s5 / s2 - s4) / (s1 * s3 / s2 - s2);
  a0 = (s4 - s2 * a1) / s1;
  return true;
}

D_Point LinearFitting::PointProjectionLine(D_Point point, double a0, double a1) {
  double x = (point.y() * a1 + point.x() - a0 * a1) / (a1 * a1 + 1);
  double y = a1 * x + a0;
  return D_Point(x, y);
}
