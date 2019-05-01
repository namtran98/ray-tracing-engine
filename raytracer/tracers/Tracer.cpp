#include "Tracer.hpp"
#include "../utilities/Constants.hpp"

Tracer::Tracer(){
    world_ptr = NULL;
}


Tracer::Tracer(World* world_pointer){
    world_ptr = world_pointer;
}


Tracer::~Tracer() {
	if (world_ptr)
		world_ptr = NULL;
}

RGBColor Tracer::trace_ray(const Ray& ray) const {
	return (black);
}
