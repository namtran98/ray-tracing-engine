#include "Grid.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/OurMath.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../geometry/MeshTriangle.hpp"
#include "../acceleration/Compound.hpp"
#include "BBox.hpp"
#include <cmath>

// Constructor
Grid::Grid() : Acceleration(), nx(0), ny(0), nz(0) {}									

Grid* Grid::clone() const {
    return new Grid (*this);
}

BBox Grid::get_bounding_box() {
    return bbox;
}

void Grid::setup_cells() {
    // find the min and max coordinates of the grid
    Point3D pMin = min_coordinates();
    Point3D pMax = max_coordinates();

    // store them in the bounding box
    bbox.min_point.x = pMin.x; 
    bbox.min_point.y = pMin.y; 
    bbox.min_point.z = pMin.z;

    bbox.max_point.x = pMax.x; 
    bbox.max_point.y = pMax.y; 
    bbox.max_point.z = pMax.z;

    // compute the number of cells in the x, y, and z-directions
    int num_objects = objects.size();
    float wx = pMax.x - pMin.x;        // grid extent in x-dir
    float wy = pMax.y - pMin.y;        // grid extent in y-dir
    float wz = pMax.z - pMax.z;        // grid extent in z-dir
    float multiplier = 2.0;            // about 8 times more cells than objects
    float s = std::pow(wx * wy * wz / num_objects, 0.33333333);

    nx = multiplier * wx / s + 1;
    ny = multiplier * wy / s + 1;
    nz = multiplier * wz / s + 1;

    // setup array of cells with null pointers
    int num_cells = nx * ny * nz;
    cells.reserve(num_objects);

    for (int i = 0; i < num_objects; i++) {
        cells.push_back(NULL);
    }

    // setup temporary array to hold the number of objects stored in each cell
    std::vector<int> counts;
    counts.reserve(num_cells);

    for (int j = 0; j < num_cells; j++) {
        counts.push_back(0);
    }

    // put objects into the cells
    BBox obj_bbox;    // object's bounding box
    int index;        // cells array index

    for (int k = 0; k < num_objects; k++) {
        obj_bbox = objects[k]->get_bounding_box();

        // compute cell indices for corners of bounding box of the object
        int ixmin = OurMath::clamp((obj_bbox.min_point.x - pMin.x) * nx / 
                            (pMax.x - pMin.x), 0, nx - 1);
        int iymin = OurMath::clamp((obj_bbox.min_point.y - pMin.y) * ny / 
                            (pMax.y - pMin.y), 0, ny - 1);
        int izmin = OurMath::clamp((obj_bbox.min_point.z - pMin.z) * nz / 
                            (pMax.z - pMin.z), 0, nz - 1);

        int ixmax = OurMath::clamp((obj_bbox.max_point.x - pMin.x) * nx / 
                            (pMax.x - pMin.x), 0, nx - 1);
        int iymax = OurMath::clamp((obj_bbox.max_point.y - pMin.y) * ny / 
                            (pMax.y - pMin.y), 0, ny - 1);
        int izmax = OurMath::clamp((obj_bbox.max_point.z - pMin.z) * nz / 
                            (pMax.z - pMin.z), 0, nz - 1);

        // add objects to the cells
        // i<direction> = initial for initial cells coordinates
        for (int iz = izmin; iz <= izmax; iz++) {          // cells in z-dir
            for (int iy = iymin; iy <= iymax; iy++) {      // cells in y-dir
                for (int ix = ixmin; ix <= ixmax; ix++) {  // cells in x-dir

                    index = ix + nx * iy + nx * ny * iz;

                    if (counts[index] == 0) {
                        cells[index] = objects[k];
                        counts[index] += 1;
                        index = 1;
                    }
                    else {
                        if (counts[index] == 1) {
                            // construct a compound object
                            Compound* compound_ptr = new Compound;

                            // add the object already in cell
                            compound_ptr->add_object(cells[index]);

                            // add the new object
                            compound_ptr->add_object(objects[k]);

                            // store compound in current cell
                            cells[index] = compound_ptr;

                            // index = 2
                            counts[index] += 1;
                        }
                        // counts [index] > 1
                        else {         
                            // just add current object
                            cells[index]->add_object(objects[k]); 

                            // for statistics only
                            counts[index] += 1;
                        }
                    }
                }
            }
        }
    }
    // erase Compound::Objects, but don't delete the objects
    objects.erase(objects.begin(), objects.end());

    // erase the temporary counts vector
    counts.erase(counts.begin(), counts.end());
}

Point3D Grid::min_coordinates() {
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

Point3D Grid::max_coordinates() {
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

//first add from mesh and then compute normals
void Grid::add_from_mesh(Mesh* m_ptr, Material* mat){
    for(int i = 0; i < m_ptr->num_triangles; i++){
        MeshTriangle* meshTri = new MeshTriangle(m_ptr, m_ptr->tris[i][0],m_ptr->tris[i][1],m_ptr->tris[i][2]);
        meshTri->set_material(mat);
        add_object(meshTri);
    }
}

void Grid::compute_normals(Mesh* m_ptr){
     // calculates normals for the faces, this will need to happen in whatever adds the grid to the scene
  m_ptr->normals.reserve(m_ptr->num_vertices);
	
	for (int index = 0; index < m_ptr->num_vertices; index++) {
		Vector3D normal;    
			
		for (int j = 0; j < m_ptr->vertex_faces[index].size(); j++){
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
        for (int j = 0; j < m_ptr->vertex_faces[index].size(); j++){
            m_ptr->vertex_faces[index].erase (m_ptr->vertex_faces[index].begin(), m_ptr->vertex_faces[index].end());
            m_ptr->tris[index].erase (m_ptr->tris[index].begin(), m_ptr->tris[index].end());
        }
    }
		
	m_ptr->vertex_faces.erase (m_ptr->vertex_faces.begin(), m_ptr->vertex_faces.end());
	m_ptr->tris.erase (m_ptr->tris.begin(), m_ptr->tris.end());
}

bool Grid::hit(const Ray& ray, World& world) const {
    double origX = ray.o.x;         // ray origin x-coord
    double origY = ray.o.y;         // ray origin y-coord
    double origZ = ray.o.z;         // ray origin z-coord

    double dirX = ray.d.x;          // ray x-direction
    double dirY = ray.d.y;          // ray y-direction
    double dirZ = ray.d.z;          // ray z-direction

    // save bounding box coordinates
    double minX = bbox.min_point.x; 
    double minY = bbox.min_point.y; 
    double minZ = bbox.min_point.z;

    double maxX = bbox.max_point.x; 
    double maxY = bbox.max_point.y; 
    double maxZ = bbox.max_point.z;

    // setup vars for tracking ray traversal
    double t_x_min, t_y_min, t_z_min;
    double t_x_max, t_y_max, t_z_max;

    // constants (denoted k<direction>) determining position relative to cell
    double kx = 1.0 / dirX;       
    if (kx >= 0) {
        t_x_min = (minX - origX) * kx;
        t_x_max = (maxX - origX) * kx;
    }
    else {
        t_x_min = (maxX - origX) * kx;
        t_x_max = (minX - origX) * kx;
    }

    double ky = 1.0 / dirY;
    if (ky >= 0) {
        t_y_min = (minY - origY) * ky;
        t_y_max = (maxY - origY) * ky;
    }
    else {
        t_y_min = (maxY - origY) * ky;
        t_y_max = (minY - origY) * ky;
    }

    double kz = 1.0 / dirZ;
    if (kz >= 0) {
        t_z_min = (minZ - origZ) * kz;
        t_z_max = (maxZ - origZ) * kz;
    }
    else {
        t_z_min = (maxZ - origZ) * kz;
        t_z_max = (minZ - origZ) * kz;
    }

    // t_hit value where the ray hits the bounding box
    double t_hit_min, t_hit_max;

    // determine min ray parameter for entering a cell
    if (t_x_min > t_y_min) {
        t_hit_min = t_x_min;
    }
    else{
        t_hit_min = t_y_min;
    }

    if (t_z_min > t_hit_min) {
        t_hit_min = t_z_min;
    }

    // determine max ray parameter for entering a cell
    if (t_x_max < t_y_max) {
        t_hit_max = t_x_max;
    }
    else {
        t_hit_max = t_y_max;
    }

    if (t_z_max < t_hit_max) {
        t_hit_max = t_z_max;
    }

    // initial cell coordinates
    int ix, iy, iz;

    // checks if the ray starts inside our grid
    if (bbox.inside(ray.o)) {
        ix = OurMath::clamp((origX - minX) * nx / (maxX - minX), 0, nx - 1);
        iy = OurMath::clamp((origY - minY) * ny / (maxY - minY), 0, ny - 1);
        iz = OurMath::clamp((origZ - minZ) * nz / (maxZ - minZ), 0, nz - 1);
    }
    else {
        // initial hit point with grid's bounding box
        Point3D init_hit = ray.o + t_hit_min * ray.d;
        ix = OurMath::clamp((init_hit.x - minX) * nx / (maxX - minX), 0, nx - 1);
        iy = OurMath::clamp((init_hit.y - minY) * ny / (maxY - minY), 0, ny - 1);
        iz = OurMath::clamp((init_hit.z - minZ) * nz / (maxZ - minZ), 0, nz - 1);
    }

    // ray parameters increment per cell in x,y,z directions
    double dtx = (t_x_max - t_x_min) / nx;   // x-dir location
    double dty = (t_y_max - t_y_min) / ny;   // y-dir location
    double dtz = (t_z_max - t_z_min) / nz;   // z-dir location

    double tx_next, ty_next, tz_next;        // track dir-face we will hit next
    int ix_step, iy_step, iz_step;           // track steps from starting spot
    int ix_stop, iy_stop, iz_stop;           // tells us when we will exit grid

    // setup x values
    if (dirX > 0) {
        tx_next = t_x_min + (ix + 1) * dirX;
        ix_step = +1;
        ix_stop = nx;
    }
    else {
        tx_next = t_x_min + (nx - ix) * dirX;
        ix_step = -1;
        ix_stop = -1;
    }

    if (dirX == 0.0) {
		tx_next = kHugeValue;
		ix_step = -1;
		ix_stop = -1;
	}

    // setup y values
    if (dirY > 0) {
		ty_next = t_y_min + (iy + 1) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else {
		ty_next = t_y_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}
	
	if (dirY == 0.0) {
		ty_next = kHugeValue;
		iy_step = -1;
		iy_stop = -1;
	}

    // setup z values
    if (dirZ > 0) {
		tz_next = t_z_min + (iz + 1) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else {
		tz_next = t_z_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}
	
	if (dirZ == 0.0) {
		tz_next = kHugeValue;
		iz_step = -1;
		iz_stop = -1;
	}

    ShadeInfo sinfo = ShadeInfo(world);
    float t = kHugeValue;
    Material* material_ptr = nullptr;

    // finally traverse the grid
    while (true) {
        Geometry* object_ptr = cells[ix + nx * iy + nx * ny * iz];

        if (tx_next < ty_next && tx_next < tz_next) {
			if (object_ptr && object_ptr->hit(ray, t, sinfo) && t < tx_next) {
				material_ptr = object_ptr->get_material();
				return (true);
			}
			
			tx_next += dtx;
			ix += ix_step;
						
			if (ix == ix_stop)
				return (false);
		}
        else { 	
			if (ty_next < tz_next) {
				if (object_ptr && object_ptr->hit(ray, t, sinfo) && t < ty_next) {
					material_ptr = object_ptr->get_material();
					return (true);
				}
				
				ty_next += dty;
				iy += iy_step;
								
				if (iy == iy_stop)
					return (false);
		 	}
		 	else {		
				if (object_ptr && object_ptr->hit(ray, t, sinfo) && t < tz_next) {
					material_ptr = object_ptr->get_material();
					return (true);
				}
				
				tz_next += dtz;
				iz += iz_step;
								
				if (iz == iz_stop)
					return (false);
		 	}
		}
    }
}