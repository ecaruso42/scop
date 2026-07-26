#pragma once

#include "Vertex.hpp"

#include <vector>
#include <string>

class ObjLoader{
	private:
    	std::vector<Vertex> _vertices;
    	std::vector<unsigned int> _indices;

		void normalizeModel();

	public:
    	ObjLoader(const std::string& path);

    	const std::vector<Vertex>& getVertices() const;
    	const std::vector<unsigned int>& getIndices() const;
};