/**
   This builds a simple scene that consists fish under the sea.
   Perspective viewing is used.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../materials/Cosine.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/Mesh.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/MeshTriangle.hpp"
#include "../lights/Point.hpp"
#include "../lights/Ambient.hpp"

#include <iostream>
void World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 500;
  vplane.vres = 500;

  // Background color.
  bg_color = oceanBlue;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Simple>(camera_ptr.get(), &vplane);
  set_ambient_light(new Ambient(1, 1, 1, .1));
  add_light(new Point(white, 1, Point3D(0,0,200)));

  // will get seg fault unless add normals
  Mesh* mesher = new Mesh((char*)"../resources/goldfish_low_res.ply");

  for(int i = 0; i < mesher->num_triangles; i++){
    MeshTriangle* meshTri1 = new MeshTriangle(mesher, std::get<0>(mesher->tris[i]), std::get<1>(mesher->tris[i]), std::get<2>(mesher->tris[i]));
    meshTri1->set_material(new Cosine(red));
    // mesher->normals.push_back(meshTri1->compute_normal());
    add_object(meshTri1);
  }

  // calculates normals for the faces, this will need to happen in whatever adds the grid to the scene
  mesher->normals.reserve(mesher->num_vertices);

	for (int index = 0; index < mesher->num_vertices; index++) {
		Vector3D normal;

		for (unsigned int j = 0; j < mesher->vertex_faces[index].size(); j++){
			normal += ((MeshTriangle*)geometry[mesher->vertex_faces[index][j]])->get_normal();
    }

		if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0){
			normal.y = 1.0;
    }
		else {
			normal.normalize();
    }

		mesher->normals.push_back(normal);
	}

  // // second fish
  // Mesh* mesher2 = new Mesh((char*)"../resources/goldfish_low_res.ply", 10, 0, 0);

  // for(int i = 0; i < mesher2->num_triangles; i++){
  //   MeshTriangle* meshTri2 = new MeshTriangle(mesher2, std::get<0>(mesher2->tris[i]), std::get<1>(mesher2->tris[i]), std::get<2>(mesher2->tris[i]));
  //   meshTri2->set_material(new Cosine(red));
  //   add_object(meshTri2);
  // }

  // // calculates normals for the faces, this will need to happen in whatever adds the grid to the scene
  // mesher2->normals.reserve(mesher2->num_vertices);

	// for (int index = 0; index < mesher2->num_vertices; index++) {
	// 	Vector3D normal;

	// 	for (unsigned int j = 0; j < mesher2->vertex_faces[index].size(); j++){
	// 		normal += ((MeshTriangle*)geometry[mesher2->vertex_faces[index][j]])->get_normal();
  //   }

	// 	if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0){
	// 		normal.y = 1.0;
  //   }
	// 	else {
	// 		normal.normalize();
  //   }

	// 	mesher2->normals.push_back(normal);
	// }

  // spheres
  Sphere* sphere_ptr1 = new Sphere(Point3D(-25, 30, -30), 20);
  sphere_ptr1->set_material(new Cosine(skyBlue)); 
  add_object(sphere_ptr1);

  Sphere* sphere_ptr2 = new Sphere(Point3D(-13, 30, -30), 20);
  sphere_ptr2->set_material(new Cosine(skyBlue));  
  add_object(sphere_ptr2);

  Sphere* sphere_ptr3 = new Sphere(Point3D(0, 30, -30), 20);
  sphere_ptr3->set_material(new Cosine(skyBlue));  
  add_object(sphere_ptr3);

  Sphere* sphere_ptr4 = new Sphere(Point3D(13, 30, -30), 20);
  sphere_ptr4->set_material(new Cosine(skyBlue));  
  add_object(sphere_ptr4);

  Sphere* sphere_ptr5 = new Sphere(Point3D(25, 30, -30), 20);
  sphere_ptr5->set_material(new Cosine(skyBlue)); 
  add_object(sphere_ptr5);
}