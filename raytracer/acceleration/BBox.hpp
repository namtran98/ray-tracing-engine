#include "../utilities/Ray.hpp"

class BBox {
public:
  BBox();
  BBox(Point3D min, Point3D max);
  ~BBox();
  BBox(const BBox& v);
  BBox& operator= (const BBox& rhs);

  bool hit(const Ray& ray) const;
  bool inside(const Point3D& p) const;

  Point3D min_point; // (x0, y0, z0)
  Point3D max_point; // (x1, y1, z1)
};
