class TriPoint {
 public:
  TriPoint(double x = 0., double y = 0., double z = 0.);

  double x() const {
    return x_;
  }

  double y() const {
    return y_;
  }

  double z() const {
    return z_;
  }

 private:
  double x_;
  double y_;
  double z_;
 
}; // class TriPoint
