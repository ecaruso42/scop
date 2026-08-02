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

	if (_faceVertices.empty()){
    	std::cerr << "OBJ contains no faces\n";
    	return;
	}

std::cout << "Positions: " << _positions.size() << std::endl;
std::cout << "Indices: " << _indices.size() << std::endl;

	buildVertices();
	std::cout << "Vertices built" << std::endl;
	calculateNormals();
	std::cout << "Normals calculated" << std::endl;
	normalizeModel();

	std::cout << "positions: "
          << _positions.size() << std::endl;

std::cout << "texCoords: "
          << _texCoords.size() << std::endl;

std::cout << "normals: "
          << _normals.size() << std::endl;

std::cout << "face vertices: "
          << _faceVertices.size() << std::endl;

std::cout << "vertices GPU: "
          << _vertices.size() << std::endl;
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
    std::vector<FaceVertex> face;

    std::string token;

    while(ss >> token)
    {
        face.push_back(parseFaceVertex(token));
    }


    for(size_t i = 2; i < face.size(); i++)
    {
        _faceVertices.push_back(face[0]);
        _faceVertices.push_back(face[i - 1]);
        _faceVertices.push_back(face[i]);
    }
}

ObjLoader::FaceVertex ObjLoader::parseFaceVertex(const std::string &token){
	FaceVertex vertex;

    std::stringstream ss(token);

    std::string value;

    if (std::getline(ss, value, '/'))
    {
        if (!value.empty())
            vertex.position = std::atoi(value.c_str()) - 1;
    }

    if (std::getline(ss, value, '/'))
    {
        if (!value.empty())
            vertex.texCoord = std::atoi(value.c_str()) - 1;
    }

    if (std::getline(ss, value, '/'))
    {
        if (!value.empty())
            vertex.normal = std::atoi(value.c_str()) - 1;
    }

    return vertex;
}

void ObjLoader::calculateNormals()
{
    for(size_t i = 0; i < _vertices.size(); i += 3)
    {
        Vector3 v0 = _vertices[i].position;
        Vector3 v1 = _vertices[i+1].position;
        Vector3 v2 = _vertices[i+2].position;


        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;


        Vector3 normal = edge1.cross(edge2);

        normal.normalize();


        _vertices[i].normal = normal;
        _vertices[i+1].normal = normal;
        _vertices[i+2].normal = normal;
    }
}

void ObjLoader::buildVertices()
{
    for(size_t i = 0; i < _faceVertices.size(); i++)
    {
        FaceVertex fv = _faceVertices[i];

        Vertex vertex;

		vertex.position = _positions[fv.position];

        if(fv.position >= 0 &&
           fv.position < (int)_positions.size())
        {
            vertex.position = _positions[fv.position];
        }


        if(fv.texCoord >= 0 &&
           fv.texCoord < (int)_texCoords.size())
        {
            vertex.texCoord = _texCoords[fv.texCoord];
        }
        else
        {
            vertex.texCoord = Vector2(
    			vertex.position.x + 0.5f,
    			vertex.position.y + 0.5f);
        }


        if(fv.normal >= 0 &&
           fv.normal < (int)_normals.size())
        {
            vertex.normal = _normals[fv.normal];
        }
        else
        {
            vertex.normal = Vector3(0,0,0);
        }


        vertex.color = Vector3(1,1,1);


        _vertices.push_back(vertex);
        _indices.push_back(i);
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