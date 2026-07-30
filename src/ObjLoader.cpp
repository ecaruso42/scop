#include "ObjLoader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

ObjLoader::ObjLoader(const std::string& path)
{
    std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << path << std::endl;
		return;
	}

	std::string line;

	while(std::getline(file, line)){
		std::stringstream ss(line);

		std::string type;

		ss >> type;

		if(type == "v"){
			parseVertex(ss);
		}
		else if(type == "vt"){
			parseTexCoord(ss);
		}
		else if(type == "vn"){
			parseNormal(ss);
		}
		else if(type == "f"){
			parseFace(ss);
		}
	}
	
	if (_positions.empty()){
    	std::cerr << "OBJ contains no vertices\n";
    	return;
	}

	if (_indices.empty()){
    	std::cerr << "OBJ contains no faces\n";
    	return;
	}

	buildVertices();
	normalizeModel();
}

void ObjLoader::parseVertex(std::stringstream& ss)
{
    float x, y, z;
    ss >> x >> y >> z;
    _positions.push_back(Vector3(x, y, z));
}

void ObjLoader::parseTexCoord(std::stringstream& ss)
{
    float u, v;
    ss >> u >> v;
    _texCoords.push_back(Vector2(u, v));
}

void ObjLoader::parseNormal(std::stringstream& ss)
{
    float x, y, z;
    ss >> x >> y >> z;
    _normals.push_back(Vector3(x, y, z));
}

void ObjLoader::parseFace(std::stringstream& ss)
{
    std::vector<unsigned int> face;

    unsigned int index;

    while(ss >> index){
        face.push_back(index - 1);
    }
    for(size_t i = 2; i < face.size(); i++){
        _indices.push_back(face[0]);
        _indices.push_back(face[i - 1]);
        _indices.push_back(face[i]);
    }
}

void ObjLoader::buildVertices()
{
    for (size_t i = 0; i < _positions.size(); i++)
    {
        Vertex vertex;

        vertex.position = _positions[i];
        vertex.texCoord = Vector2(0,0);
        vertex.normal = Vector3(0,0,1);
        vertex.color = Vector3(1,1,1);

        _vertices.push_back(vertex);
    }
}

void ObjLoader::normalizeModel()
{
    if (_vertices.empty())
        return;

    Vector3 min = _vertices[0].position;
    Vector3 max = _vertices[0].position;

    for (size_t i = 1; i < _vertices.size(); i++)
    {
        Vector3 p = _vertices[i].position;

        if (p.x < min.x) min.x = p.x;
        if (p.y < min.y) min.y = p.y;
        if (p.z < min.z) min.z = p.z;

        if (p.x > max.x) max.x = p.x;
        if (p.y > max.y) max.y = p.y;
        if (p.z > max.z) max.z = p.z;
    }

	Vector3 center = (min + max) * 0.5f;

	float sizeX = max.x - min.x;
	float sizeY = max.y - min.y;
	float sizeZ = max.z - min.z;

	float maxSize = sizeX;

	if (sizeY > maxSize)
	    maxSize = sizeY;

	if (sizeZ > maxSize)
	    maxSize = sizeZ;

	for (size_t i = 0; i < _vertices.size(); i++)
	{
    	_vertices[i].position = (_vertices[i].position - center) / maxSize;
	}
}

const std::vector<Vertex>& ObjLoader::getVertices() const{
	return _vertices;
}

const std::vector<unsigned int>& ObjLoader::getIndices() const{
	return _indices;
}