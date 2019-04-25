#include "ShadeInfo.hpp"



ShadeInfo::ShadeInfo(World& wr){
    w = std::make_unique<World>(&wr);
}

ShadeInfo::ShadeInfo(const ShadeInfo& sr){
    hit = sr.hit;  
    material_ptr = std::make_unique<Material>(material_ptr); 
    hit_point = sr.hit_point; 
    ray = sr.ray; 
    depth = sr.depth; 
    t = sr.t;
    w = std::make_unique<World>(sr.w); 
    normal = sr.normal;
}

 ShadeInfo::~ShadeInfo(){
 }