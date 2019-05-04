#pragma once
#include "Compound.hpp"
#include "BBox.hpp"
#include <vector>

class Grid: public Compound {
public:
    Grid();

    // other constructors
    virtual BBox get_bounding_box();

    void setup_cells();

    virtual bool hit(const Ray& ray, float& t, ShadeInfo& sinfo) const;

private: 
    std::vector<Geometry*> cells;   // cells are stored in a 1D array
    BBox bbox;                      // bounding box
    int nx, ny, nz;                 // number of cells in the x, y, and z-dir
    Point3D min_coordinates();      // compute minimum grid coordinates
    Point3D max_coordinates();      // compute maximum grid coordinates

};