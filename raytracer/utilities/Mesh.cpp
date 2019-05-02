#include "Mesh.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

			
		
Mesh::Mesh(char* file_name){
    std::vector<Point3D> vertices;		
    std::vector<Vector3D> normals;		
    std::vector<std::vector<int>> vertex_faces;
    std::vector<std::vector<int>> tris;
    num_vertices=0; 			
    num_triangles=0; 
    populate(file_name);
}		
    
Mesh::Mesh(const Mesh& m){
    vertices = m.vertices;
    normals = m.normals;
    vertex_faces = m.vertex_faces;
    num_vertices = m.num_vertices;
    num_triangles = m.num_triangles;
    tris = m.tris;
}						

Mesh::~Mesh(){
}					

Mesh& Mesh::operator= (const Mesh& rhs){
    vertices = rhs.vertices;
    normals = rhs.normals;
    vertex_faces = rhs.vertex_faces;
    num_vertices = rhs.num_vertices;
    num_triangles = rhs.num_triangles;
    tris = rhs.tris;
    return *this;
}

void Mesh::populate(char* file_name){
    std::ifstream file;
    file.open(file_name);
    if (file.is_open()) {
        std::string line;
        int verticeCount = 0;
        int triangleCount = 0;
        bool inHeader = true;
        while (getline(file, line)) {
            if(line.compare("")==0)
                break;
            std::vector<std::string> result;
            std::istringstream iss(line);
            for(std::string line; iss >> line;){
                result.push_back(line);
            }
            if(inHeader){
                if(result[0].compare("element")==0&&result[1].compare("vertex")==0){
                    num_vertices = std::stoi(result[2]);
                    vertices.reserve(num_vertices);
                    vertex_faces.reserve(num_vertices);
                }
                else if(result[0].compare("element")==0&&result[1].compare("face")==0){
                    num_triangles = std::stoi(result[2]);
                    tris.reserve(num_triangles);
                }
                else if(result[0].compare("end_header")==0){
                    inHeader = false;
                }
            }
            else if(verticeCount < num_vertices){
                float x = std::stof(result[0]);
                float y = std::stof(result[1]);
                float z = std::stof(result[2]);
                vertices.push_back(Point3D(x,y,z));
                verticeCount++;
            }
            else if(triangleCount<num_triangles){
                std::vector<int> smoltri;
                smoltri.push_back(std::stoi(result[1]));
                smoltri.push_back(std::stoi(result[2]));
                smoltri.push_back(std::stoi(result[3]));
                tris.push_back(smoltri);
                // add face to the vertices count
                vertex_faces[std::stoi(result[1])].push_back(triangleCount);
                vertex_faces[std::stoi(result[2])].push_back(triangleCount);
                vertex_faces[std::stoi(result[3])].push_back(triangleCount);
                triangleCount++;
            }
        }
        file.close();
    }
}