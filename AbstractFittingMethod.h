#ifndef FITTINGMETHOD_ABSTRACTFITTINGMETHOD_H__
#define FITTINGMETHOD_ABSTRACTFITTINGMETHOD_H__

#include <vector>

#include "D_Point.h"

class AbstractFittingMethod {
 public:
  AbstractFittingMethod() {}
  virtual ~AbstractFittingMethod() {}

  virtual bool CurveFitting(const std::vector<D_Point> &src_points,
	                          std::vector<D_Point> &dst_points) = 0;

}; // class AbstractFittingMethod

#endif // FITTINGMETHOD_ABSTRACTFITTINGMETHOD_H__
