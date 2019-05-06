#include "Acceleration.hpp"

Acceleration::Acceleration(){
} 

// Copy constructor and assignment operator.
Acceleration::Acceleration(const Acceleration& rhs){

}


void Acceleration::add_object(Geometry* object_ptr) {
    objects.push_back(object_ptr); 
}


int Acceleration::get_num_objects() {
    return objects.size();
}


Acceleration& Acceleration::operator= (const Acceleration& rhs){
    return *this;
}


// Desctructor.
Acceleration::~Acceleration(void){

}  // dummy function.
