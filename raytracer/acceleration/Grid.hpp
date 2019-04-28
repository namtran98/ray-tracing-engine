#pragma once
#include "Compound.hpp"
#include "BBox.hpp"
#include <vector>


class Grid: public Compound {
public:
    Grid(void);

    // other constructors
     
     virtual BBox get_bounding_box(void);

     void setup_cells(void);

     virtual bool hit(Ray& ray, float& t_min, ShadeInfo& s);

     virtual bool shadow_hit(Ray& ray, float& t_min);

private: 
    std::vector<Geometry*> cells;   // cells are stored in a 1D array
    BBox bbox;                      // bounding box
    int nx, ny, nz;                 // number of cells in the x, y, and z-dir
    Point3D min_coordinates(void);  // compute minimum grid coordinates
    Point3D max_coordinates(void);  // compute maximum grid coordinates

}