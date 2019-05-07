#include "MeshTriangle.hpp"
#include "../utilities/Constants.hpp"
#include <algorithm>

#include <iostream>
MeshTriangle::MeshTriangle(){
  mesh_ptr = NULL;
  index0 = 0;
  index1 = 1;
  index2 = 2;
  normal = Vector3D(0);
  bbox = get_bounding_box();
}

MeshTriangle::MeshTriangle(Mesh* m_ptr, const int i0, const int i1, const int i2){
  mesh_ptr = m_ptr;
  index0 = i0;
  index1 = i1;
  index2 = i2;
  bbox = get_bounding_box();
}

MeshTriangle* MeshTriangle::clone() const{
  return new MeshTriangle(*this);
}

MeshTriangle::MeshTriangle(const MeshTriangle& mt){
  mesh_ptr = mt.mesh_ptr;
  index0 = mt.index0;
  index1 = mt.index1;
  index2 = mt.index2;
  normal = mt.normal;
  bbox = mt.bbox;
}

MeshTriangle::~MeshTriangle(){}

MeshTriangle& MeshTriangle::operator= (const MeshTriangle& rhs){
  mesh_ptr = rhs.mesh_ptr;
  index0 = rhs.index0;
  index1 = rhs.index1;
  index2 = rhs.index2;
  normal = rhs.normal;
  bbox = rhs.bbox;
  return *this;
}

bool MeshTriangle::hit(const Ray& ray, float& t_min, ShadeInfo& si) const{
  if (not bbox.hit(ray)){
    return false;
  }

  Point3D v0 = Point3D(mesh_ptr->vertices[index0]);
	Point3D v1 = Point3D(mesh_ptr->vertices[index1]);
	Point3D v2 = Point3D(mesh_ptr->vertices[index2]);
  Vector3D edge1, edge2, h, s, q;
  float _a, f, u, v;
  edge1 = v1-v0;
  edge2 = v2-v0;
  h = ray.d ^ edge2;
  _a = edge1 * h;
  if (_a > -kEpsilon && _a < kEpsilon){
    return false; // ray parallel to triangle
  }
  f = 1.0 / _a;
  s = ray.o - v0;
  u = f * (s * h);
  if (u < 0.0 || u > 1.0){
    return false;
  }
  q = s ^ edge1;
  v = f * (ray.d * q);
  if (v < 0.0 || u + v > 1.0){
    return false;
  }
  float t = f * (edge2 * q);
  if (t > kEpsilon){
    si.hit_point = ray.o + (ray.d * t);
    si.normal = edge1 ^ edge2;
    si.hit = true;
    si.material_ptr = material_ptr;
    si.ray = ray;
    t_min = t;
    si.t = t;
    return true;
  } else {
    return false; // Line intersects but before the origin
  }
}

BBox MeshTriangle::get_bounding_box(){
  double delta = 0.0001;

	Point3D v1 = Point3D(mesh_ptr->vertices[index0]);
	Point3D v2 = Point3D(mesh_ptr->vertices[index1]);
	Point3D v3 = Point3D(mesh_ptr->vertices[index2]);
  Point3D min = Point3D(std::min(std::min(v1.x, v2.x), v3.x) - delta, std::min(std::min(v1.y, v2.y), v3.y) - delta, std::min(std::min(v1.z, v2.z), v3.z) - delta);
  Point3D max = Point3D(std::max(std::max(v1.x, v2.x), v3.x) + delta, std::max(std::max(v1.y, v2.y), v3.y) + delta, std::max(std::max(v1.z, v2.z), v3.z) + delta);

	return BBox(min, max);
}

Vector3D MeshTriangle::get_normal() const{
  return normal;
}

Vector3D MeshTriangle::compute_normal(){
  normal = (mesh_ptr->vertices[index1] - mesh_ptr->vertices[index0]) ^ (mesh_ptr->vertices[index2] - mesh_ptr->vertices[index0]);
	normal.normalize();
  return normal;
}

Vector3D MeshTriangle::interpolate_normal(const float beta, const float gamma) const{
  Vector3D normal = Vector3D((1 - beta - gamma) * mesh_ptr->normals[index0] + beta * mesh_ptr->normals[index1] + gamma * mesh_ptr->normals[index2]);
	normal.normalize();
	return normal;
}
