#pragma once


#include "IndexedTrigList.h"
#include "Math.h"

#include <vector>
#include <array>


class VoxelGrid
{
public:

    template<typename VERTEX>
    static IndexedTrigList<VERTEX> MakeTesselated(int xDivisions, int yDivisions, int zDivisions)
    {
        assert(xDivisions >= 1);
        assert(yDivisions >= 1);
        assert(zDivisions >= 1);


        constexpr float width = 2.0f;
        constexpr float height = 2.0f;
        constexpr float length = 2.0f;


        const int nXVertices = xDivisions + 1;
        const int nYVertices = yDivisions + 1;
        const int nZVertices = zDivisions + 1;


        std::vector<glm::vec3> vertices(nXVertices * nYVertices * nZVertices);

        const float xSide = width / 2.0f;
        const float ySide = height / 2.0f;
        const float zSide = length / 2.0f;


        /// Grid cell/quad width and height sizes
        const float xDivisionSize = width / float(xDivisions);
        const float yDivisionSize = height / float(yDivisions);
        const float zDivisionSize = height / float(zDivisions);


        glm::vec3 bottomLeft = glm::vec3(-xSide, -ySide, -zSide);

        for (int z = 0, i = 0; z < nZVertices; z++)
        {
            const float zPos = float(z) * zDivisionSize;

            for (int y = 0; y < nYVertices; y++)
            {
                const float yPos = float(y) * yDivisionSize;

                for (int x = 0; x < nXVertices; x++, i++)
                {
                    const float xPos = float(x) * xDivisionSize;

                    /// The postion values of the vertex relative to the origin
                    glm::vec3 relativeVertex = glm::vec3(xPos, yPos, zPos);
                    /// The absoulte postion values of the vertex in 3D Space
                    glm::vec3 vertex = bottomLeft + relativeVertex;

                    vertices[i] = vertex;
                }
            }
        }

        std::vector<VERTEX> verts(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts[i].pos = vertices[i];
        }

        std::vector<unsigned int> indices;

        indices.reserve(xDivisions * yDivisions * zDivisions * 36); // 6 faces per cell, 6 indices per face

        // Function that returns the index of a vertex in a 3D vertices vector
        const auto v2i = [nXVertices, nYVertices](size_t x, size_t y, size_t z)
            {
                return (unsigned int)(z * nXVertices * nYVertices + y * nXVertices + x);
            };

        // Loop over each cell in the 3D grid
        for (size_t z = 0; z < zDivisions; z++)
        {
            for (size_t y = 0; y < yDivisions; y++)
            {
                for (size_t x = 0; x < xDivisions; x++)
                {
                    const std::array<unsigned int, 8> indexArray =
                    {
                        v2i(x, y, z),           // Bottom-front-left
                        v2i(x + 1, y, z),       // Bottom-front-right
                        v2i(x, y + 1, z),       // Top-front-left
                        v2i(x + 1, y + 1, z),   // Top-front-right
                        v2i(x, y, z + 1),       // Bottom-back-left
                        v2i(x + 1, y, z + 1),   // Bottom-back-right
                        v2i(x, y + 1, z + 1),   // Top-back-left
                        v2i(x + 1, y + 1, z + 1)// Top-back-right
                    };

                    // Front face
                    indices.push_back(indexArray[0]);
                    indices.push_back(indexArray[2]);
                    indices.push_back(indexArray[1]);
                    indices.push_back(indexArray[1]);
                    indices.push_back(indexArray[2]);
                    indices.push_back(indexArray[3]);

                    // Back face
                    indices.push_back(indexArray[4]);
                    indices.push_back(indexArray[5]);
                    indices.push_back(indexArray[6]);
                    indices.push_back(indexArray[5]);
                    indices.push_back(indexArray[7]);
                    indices.push_back(indexArray[6]);

                    // Left face
                    indices.push_back(indexArray[0]);
                    indices.push_back(indexArray[4]);
                    indices.push_back(indexArray[2]);
                    indices.push_back(indexArray[2]);
                    indices.push_back(indexArray[4]);
                    indices.push_back(indexArray[6]);

                    // Right face
                    indices.push_back(indexArray[1]);
                    indices.push_back(indexArray[3]);
                    indices.push_back(indexArray[5]);
                    indices.push_back(indexArray[3]);
                    indices.push_back(indexArray[7]);
                    indices.push_back(indexArray[5]);

                    // Top face
                    indices.push_back(indexArray[2]);
                    indices.push_back(indexArray[6]);
                    indices.push_back(indexArray[3]);
                    indices.push_back(indexArray[3]);
                    indices.push_back(indexArray[6]);
                    indices.push_back(indexArray[7]);

                    // Bottom face
                    indices.push_back(indexArray[0]);
                    indices.push_back(indexArray[1]);
                    indices.push_back(indexArray[4]);
                    indices.push_back(indexArray[1]);
                    indices.push_back(indexArray[5]);
                    indices.push_back(indexArray[4]);
                }
            }
        }

        return{ std::move(verts),std::move(indices) };
    }


    template<typename V>
    static IndexedTrigList<V> Make()
    {
        return MakeTesselated<V>(32, 32,32);
    }

};
