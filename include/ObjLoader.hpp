#pragma once

#include "Vertex.hpp"

#include <vector>
#include <string>

class ObjLoader{
	private:
    	std::vector<Vertex> _vertices;
    	std::vector<unsigned int> _indices;

		std::vector<Vector3> _positions;
		std::vector<Vector2> _texCoords;
		std::vector<Vector3> _normals;

		void parseVertex(std::stringstream& ss);
		void parseTexCoord(std::stringstream& ss);
		void parseNormal(std::stringstream& ss);
		void parseFace(std::stringstream& ss);

		void calculateNormals();
		void buildVertices();
		void normalizeModel();

	public:
    	ObjLoader(const std::string& path);

    	const std::vector<Vertex>& getVertices() const;
    	const std::vector<unsigned int>& getIndices() const;
};