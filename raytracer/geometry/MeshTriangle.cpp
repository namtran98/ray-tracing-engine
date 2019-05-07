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
  // std::cout <<"hello"<<"\n";
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom  = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0){
    return false;
  }

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0){
    return false;
  }

	if (beta + gamma > 1.0){
    return false;
  }

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon){
    return false;
  }

  si.hit = true;
  si.material_ptr = material_ptr;
  si.ray = ray;
  t_min = t;
	si.normal = interpolate_normal(beta, gamma); // for smooth shading
	si.hit_point = ray.o + t * ray.d;
	si.t = t;
	return true;
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
