#pragma once
#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"

class World;

class Tracer {
    protected:
        World* world_ptr;

	public:
		Tracer();									
		
		Tracer(World* _world_ptr);						
				
		virtual	~Tracer();									

		virtual RGBColor trace_ray(const Ray& ray) const;
};
