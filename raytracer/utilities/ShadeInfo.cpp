#include "ShadeInfo.hpp"
#include "../world/World.hpp"



ShadeInfo::ShadeInfo(World& wr){
    w =  &wr;
}

ShadeInfo::ShadeInfo(const ShadeInfo& sr){
    hit = sr.hit;  
    material_ptr = material_ptr; 
    hit_point = sr.hit_point; 
    ray = sr.ray; 
    depth = sr.depth; 
    t = sr.t;
    w = sr.w;
    normal = sr.normal;
}

 ShadeInfo::~ShadeInfo(){
 }