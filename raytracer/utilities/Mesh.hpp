#pragma once
#include <vector>

#include "Point3D.hpp"
#include "Vector3D.hpp"

class Mesh {
public:
  std::vector<Point3D> vertices;
  // normal at each vertex;
  std::vector<Vector3D> normals;
  // the triangles shared by each vertex
  std::vector<std::vector<int> > 	vertex_faces;
  std::vector<std::vector<int> > 	tris;
  int num_vertices;
  int num_triangles;
  float x_offset;
  float y_offset;
  float z_offset;

  Mesh(char* file_name);

  Mesh(const Mesh& m);

  ~Mesh();

  Mesh&
  operator= (const Mesh& rhs);

  void populate(char* file_name);

  void setOffsets(float x, float y, float z);
};
