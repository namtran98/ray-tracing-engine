/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../materials/Cosine.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/Mesh.hpp"
#include "../geometry/MeshTriangle.hpp"

#include <iostream>
void
World::build(void) {
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
  bg_color = white;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Simple>(camera_ptr.get(), &vplane);

  set_acceleration(new Grid());

  
  // will get seg fault unless add normals
  Mesh* mesher = new Mesh((char*)"goldfish_low_res.ply");
  std::cout << "hello"<<"\n";
  // for(int i = 0; i < mesher->num_triangles; i++){
  //   MeshTriangle* meshTri1 = new MeshTriangle(mesher, mesher->tris[i][0],mesher->tris[i][1],mesher->tris[i][2]);
  //   meshTri1->set_material(new Cosine(red));
  //   // mesher->normals.push_back(meshTri1->compute_normal());
  //   accel_ptr->add_object(meshTri1);
  // }
  accel_ptr->add_from_mesh(mesher, new Cosine(red));

  std::cout << "hello2"<<"\n";
  // calculates normals for the faces, this will need to happen in whatever adds the grid to the scene
  // mesher->normals.reserve(mesher->num_vertices);
	
	// for (int index = 0; index < mesher->num_vertices; index++) {
	// 	Vector3D normal;    
			
	// 	for (int j = 0; j < mesher->vertex_faces[index].size(); j++){
	// 		normal += ((MeshTriangle*)geometry[mesher->vertex_faces[index][j]])->get_normal();  
  //   }
		
	// 	if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0){
	// 		normal.y = 1.0;
  //   }
	// 	else {
	// 		normal.normalize();     
  //   }
		
	// 	mesher->normals.push_back(normal);
	// }
  
  accel_ptr->compute_normals(mesher);
  std::cout << "hello3"<<"\n";

  accel_ptr->initialize();

}
