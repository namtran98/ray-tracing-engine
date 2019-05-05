#pragma once
#include "BBox.hpp"
#include "../utilities/Mesh.hpp"
#include "Acceleration.hpp"
#include <vector>

class Grid: public Acceleration {
public:
    Grid();

    virtual Grid* clone() const;

    virtual BBox get_bounding_box();

    void setup_cells();

    void add_from_mesh(Mesh* m_ptr, Material* mat);

    // for use with add_from_mesh
    void compute_normals(Mesh* m_ptr);

    virtual bool hit(const Ray& ray, ShadeInfo& sinfo) const;

private:
    std::vector<Geometry*> cells;   // cells are stored in a 1D array
    BBox bbox;                      // bounding box
    int nx, ny, nz;                 // number of cells in the x, y, and z-dir
    Point3D min_coordinates();      // compute minimum grid coordinates
    Point3D max_coordinates();      // compute maximum grid coordinates

};
