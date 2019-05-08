#pragma once
#include "Tracer.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"



class Shadow : public Tracer{
    public:
        Shadow();									

        Shadow(World* _world_ptr);						
                
        virtual	~Shadow();									

        virtual RGBColor trace_ray(const Ray& ray) const;
};