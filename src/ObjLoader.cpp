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

std::cout << "Positions: " << _positions.size() << std::endl;
std::cout << "Indices: " << _indices.size() << std::endl;

	calculateNormals();
	std::cout << "Normals calculated" << std::endl;
	buildVertices();
	std::cout << "Vertices built" << std::endl;
	normalizeModel();
}

void ObjLoader::parseVertex(std::stringstream& ss)
{
    float x, y, z;
	if (!(ss >> x >> y >> z))
	{
    	std::cerr << "Malformed vertex\n";
    	return;
	}
    _positions.push_back(Vector3(x, y, z));
}

void ObjLoader::parseTexCoord(std::stringstream& ss)
{
    float u, v;
    if (!(ss >> u >> v))
	{
		std::cerr << "Malformed texture coordinate\n";
		return;
	}
    _texCoords.push_back(Vector2(u, v));
}

void ObjLoader::parseNormal(std::stringstream& ss)
{
    float x, y, z;
    if (!(ss >> x >> y >> z))
	{
		std::cerr << "Malformed normal\n";
		return;
	}
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

void ObjLoader::calculateNormals()
{
    _normals.resize(_positions.size(), Vector3(0,0,0));

    for (size_t i = 0; i < _indices.size(); i += 3)
    {
        unsigned int i0 = _indices[i];
        unsigned int i1 = _indices[i + 1];
        unsigned int i2 = _indices[i + 2];

        Vector3 v0 = _positions[i0];
        Vector3 v1 = _positions[i1];
        Vector3 v2 = _positions[i2];


        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;


        Vector3 normal = edge1.cross(edge2);

        normal.normalize();


        _normals[i0] = _normals[i0] + normal;
        _normals[i1] = _normals[i1] + normal;
        _normals[i2] = _normals[i2] + normal;
    }


    // normalizzazione finale
    for (size_t i = 0; i < _normals.size(); i++)
    {
        _normals[i].normalize();
    }
}

void ObjLoader::buildVertices()
{
    for (size_t i = 0; i < _positions.size(); i++)
    {
        Vertex vertex;

        vertex.position = _positions[i];
        vertex.texCoord = Vector2(0,0);
        vertex.normal = _normals[i];

		float shade = (vertex.normal.z + 1.0f) * 0.5f;

		vertex.color = Vector3(
    		shade,
    		shade,
    		shade
		);

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