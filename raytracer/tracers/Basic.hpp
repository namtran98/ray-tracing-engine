#pragma once
#include "Tracer.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"



class Basic : public Tracer{
    public:
        Basic();									

        Basic(World* _world_ptr);						
                
        virtual	~Basic();									

        virtual RGBColor trace_ray(const Ray& ray) const;
};