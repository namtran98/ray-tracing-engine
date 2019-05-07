#include "BVH.hpp"
#include "../utilities/Constants.hpp"
#include "../geometry/MeshTriangle.hpp"
#include <algorithm>

bool xInOrder(Geometry *a, Geometry*b){
  BBox aBB = a->get_bounding_box();
  BBox bBB = b->get_bounding_box();
  return (aBB.min_point.x + aBB.max_point.x) / 2 <= (bBB.min_point.x + bBB.max_point.x) / 2;
}

bool yInOrder(Geometry *a, Geometry*b){
  BBox aBB = a->get_bounding_box();
  BBox bBB = b->get_bounding_box();
  return (aBB.min_point.y + aBB.max_point.y) / 2 <= (bBB.min_point.y + bBB.max_point.y) / 2;
}

bool zInOrder(Geometry *a, Geometry*b){
  BBox aBB = a->get_bounding_box();
  BBox bBB = b->get_bounding_box();
  return (aBB.min_point.z + aBB.max_point.z) / 2 <= (bBB.min_point.z + bBB.max_point.z) / 2;
}

BVH::BVH() : split_dim(0), bbox(){}
BVH::BVH(int split) : split_dim(split){}
BVH::BVH(int split, BVH *_left, BVH *_right) : split_dim(split), left(_left), right(_right){}
BVH::~BVH(){
  if (left != nullptr){
    delete left;
  }
  if (right != nullptr){
    delete right;
  }
}

void BVH::initialize(){
  // compute current size
  Point3D pMin = min_coordinates();
  Point3D pMax = max_coordinates();
  bbox.min_point.x = pMin.x;
  bbox.min_point.y = pMin.y;
  bbox.min_point.z = pMin.z;

  bbox.max_point.x = pMax.x;
  bbox.max_point.y = pMax.y;
  bbox.max_point.z = pMax.z;
  if (objects.size() > 1){
    // make new subtrees
    left = new BVH((split_dim + 1) % 3);
    right = new BVH((split_dim + 1) % 3);
    if (split_dim == 0){
      std::sort(objects.begin(), objects.end(), xInOrder);
    } else if (split_dim == 1){
      std::sort(objects.begin(), objects.end(), yInOrder);
    } else if (split_dim == 2){
      std::sort(objects.begin(), objects.end(), zInOrder);
    }
    for(unsigned int i = 0; i < objects.size(); i++){
      if (i < objects.size() / 2){
        left->add_object(objects[i]);
      } else {
        right ->add_object(objects[i]);
      }
    }

    left->initialize();
    right->initialize();
    objects.clear();
    }
  }

Point3D BVH::min_coordinates() {
  BBox bbox;
  Point3D p0(kHugeValue);

  int num_objects = objects.size();

  for (int i = 0; i < num_objects; i++) {
    bbox = objects[i]->get_bounding_box();

    if (bbox.min_point.x < p0.x)
      p0.x = bbox.min_point.x;
    if (bbox.min_point.y < p0.y)
      p0.y = bbox.min_point.y;
    if (bbox.min_point.z < p0.z)
      p0.z = bbox.min_point.z;
  }

  p0.x -= kEpsilon;
  p0.y -= kEpsilon;
  p0.z -= kEpsilon;

  return p0;
}

Point3D BVH::max_coordinates() {
  BBox bbox;
  Point3D p0(-kHugeValue);

  int num_objects = objects.size();

  for (int i = 0; i < num_objects; i++) {
    bbox = objects[i]->get_bounding_box();

    if (bbox.max_point.x > p0.x)
      p0.x = bbox.max_point.x;
    if (bbox.max_point.y > p0.y)
      p0.y = bbox.max_point.y;
    if (bbox.max_point.z > p0.z)
      p0.z = bbox.max_point.z;
  }

  p0.x -= kEpsilon;
  p0.y -= kEpsilon;
  p0.z -= kEpsilon;

  return p0;
}

bool BVH::hit(const Ray& ray, ShadeInfo& sinfo) const{
  if (not bbox.hit(ray)){
    return false;
  }
  if (objects.size() == 1){
    float t = kHugeValue;
    return objects[0]->hit(ray, t, sinfo);
  }
  float split_dir_of_ray = 0;
  if (split_dim == 0){
    split_dir_of_ray = ray.d.x;
  } else if(split_dim == 1){
    split_dir_of_ray = ray.d.y;
  } else if(split_dim == 2){
    split_dir_of_ray = ray.d.z;
  }
  if (split_dir_of_ray > 0){
    if (left and left->hit(ray, sinfo)){
      return true;
    } else {
      if(right){
        return right->hit(ray, sinfo);
      }
    }
  } else {
    if (right and right->hit(ray, sinfo)){
      return true;
    } else {
      if(left){
        return left->hit(ray, sinfo);
      }
    }
  }
  return false;
}

BVH* BVH::clone(){
  return new BVH(split_dim, left->clone(), right->clone());
}

void BVH::add_from_mesh(Mesh *m_ptr, Material *mat){
  for(int i = 0; i < m_ptr->num_triangles; i++){
    MeshTriangle* meshTri = new MeshTriangle(m_ptr, std::get<0>(m_ptr->tris[i]), std::get<1>(m_ptr->tris[i]), std::get<2>(m_ptr->tris[i]));
    meshTri->set_material(mat);
    add_object(meshTri);
  }
}

void BVH::compute_normals(Mesh* m_ptr){
  // calculates normals for the faces, this will need to happen in whatever adds the grid to the scene
  m_ptr->normals.reserve(m_ptr->num_vertices);

	for (int index = 0; index < m_ptr->num_vertices; index++) {
		Vector3D normal;

		for (unsigned int j = 0; j < m_ptr->vertex_faces[index].size(); j++){
			normal += ((MeshTriangle*)objects[m_ptr->vertex_faces[index][j]])->get_normal();
    }

		if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0){
			normal.y = 1.0;
    }
		else {
			normal.normalize();
    }

		m_ptr->normals.push_back(normal);
	}
  // we can now erase vertex_faces array and tris array
  for (int index = 0; index < m_ptr->num_vertices; index++){
    for (unsigned int j = 0; j < m_ptr->vertex_faces[index].size(); j++){
      m_ptr->vertex_faces[index].clear();
    }
  }

	m_ptr->vertex_faces.clear();
	m_ptr->tris.clear();
}
