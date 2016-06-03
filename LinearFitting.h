#ifndef FITTINGMETHOD_LINEARFITTING_H__
#define FITTINGMETHOD_LINEARFITTING_H__

#include "AbstractFittingMethod.h"

/**
 * S(x) = a0 + a1 * x
 * 
 *
 */
class LinearFitting : public AbstractFittingMethod {
 public:
  LinearFitting() {}
  ~LinearFitting() {}

  bool CurveFitting(const std::vector<D_Point> &src_points,
	                  std::vector<D_Point> &dst_points);

 private:
  bool CalculateCoefficient(const std::vector<D_Point> &points,
                            double &a0, double &a1);

  D_Point PointProjectionLine(D_Point point, double a0, double a1);


}; // class LinearFitting

#endif // FITTINGMETHOD_LINEARFITTING_H__
