#include "ShadeInfo.hpp"
#include "../world/World.hpp"



ShadeInfo::ShadeInfo(World& wr){
    w =  &wr;
}

ShadeInfo::ShadeInfo(const ShadeInfo& sr){
    hit = sr.hit;
    material_ptr = sr.material_ptr;
    hit_point = sr.hit_point;
    local_hit_point = sr.local_hit_point;
    ray = sr.ray;
    depth = sr.depth;
    t = sr.t;
    w = sr.w;
    normal = sr.normal;
    dir = sr.dir;
}

 ShadeInfo::~ShadeInfo(){
 }
