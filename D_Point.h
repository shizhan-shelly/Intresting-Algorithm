#ifndef FITTINGMETHOD_DPOINT_H__
#define FITTINGMETHOD_DPOINT_H__

class D_Point {
 public:
  D_Point(double x = 0., double y = 0.);

  double x() const {
    return x_;
  }

  double y() const {
    return y_;
  }

  static double Distance(D_Point p1, D_Point p2);

 private:
  double x_;
  double y_;
 
}; // class D_Point

#endif // FITTINGMETHOD_DPOINT_H__