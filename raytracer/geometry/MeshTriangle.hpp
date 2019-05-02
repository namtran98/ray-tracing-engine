#pragma once 
#include "Geometry.hpp"
#include "../utilities/Mesh.hpp"


class MeshTriangle: public Geometry {	
	public:
        Mesh* mesh_ptr;	
		int	index0, index1, index2;
		Vector3D normal;	

		MeshTriangle();   									
		
		MeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);		

		virtual MeshTriangle* clone() const;
	
		MeshTriangle(const MeshTriangle& fmt); 					

		virtual ~MeshTriangle();   									

		MeshTriangle& operator= (const MeshTriangle& rhs);
				
		virtual	bool hit(const Ray& ray, float& t_min, ShadeInfo& si) const; 

        virtual BBox get_bounding_box();		

        virtual Vector3D get_normal() const;			

        void compute_normal();			

	protected:
		Vector3D interpolate_normal(const float beta, const float gamma) const;
};
