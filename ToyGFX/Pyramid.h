#pragma once

#include "IndexedTrigList.h"
#include "Math.h"

class Pyramid
{
public:

    template <typename VERTEX>
    static IndexedTrigList<VERTEX> MakeTesselated(int stacks, int sectors)
    {

        const float longitudeAngle = 2.0f * FPI / sectors;

        float sectorAngle;

        std::vector<float> baseCircle;

        for (int i = 0; i <= sectors; i++)
        {
            sectorAngle = longitudeAngle * i;
            baseCircle.push_back(cosf(sectorAngle));
            baseCircle.push_back(sinf(sectorAngle));
            baseCircle.push_back(0.0f);

        }


        float radius, height;

        float RAD = 0.5f;

        height = 2.0f;

        float x, y, z;

        std::vector<glm::vec3> vertices;


        for (int i = 0; i <= stacks; i++)
        {
            z = -(height * 0.5f) + (float)i / stacks * height;
            radius = RAD * (1.0f - (float)i / stacks);

            for (int j = 0, k = 0; j <= sectors; j++, k += 3)
            {
                x = baseCircle[k];
                y = baseCircle[k + 1];
                vertices.emplace_back(x * radius, y * radius, z);
            }
        }


        //Base vertices

        z = -height * 0.5f;

        vertices.emplace_back(0.0f, 0.0f, z);

        for (int j = 0, k = 0; j < sectors; j++, k += 3)
        {

            x = baseCircle[k];
            y = baseCircle[k + 1];
       
            vertices.emplace_back(x * RAD, y * RAD, z);
        }
        

        std::vector<VERTEX> verts(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts[i].pos = vertices[i];
        }


        std::vector<unsigned int> indices;
        unsigned int k1, k2;

        for (int i = 0; i < stacks; i++)
        {
            k1 = i * (sectors + 1);     // bebinning of current stack
            k2 = k1 + sectors + 1;      // beginning of next stack

            for (int j = 0; j < sectors; j++, k1++, k2++)
            {

                indices.push_back(k1);
                indices.push_back(k1 + 1);
                indices.push_back(k2);

                indices.push_back(k2);
                indices.push_back(k1 + 1);
                indices.push_back(k2 + 1);
            }
        }


        unsigned int baseCenterIndex = (unsigned int)(vertices.size() - sectors - 1);  // Center index of base
        unsigned int baseStartIndex = baseCenterIndex + 1;  // First vertex on the base circle

        for (int i = 0; i < sectors; i++)
        {
            if (i < (sectors - 1))
            {
                // Triangle: center of base, i-th vertex, (i+1)-th vertex
                indices.push_back(baseCenterIndex);         // Center vertex
                indices.push_back(baseStartIndex + i + 1);  // Next vertex on the circle
                indices.push_back(baseStartIndex + i);      // Current vertex on the circle
            }
            else
            {
                // Last triangle: wraps around to the first vertex
                indices.push_back(baseCenterIndex);      // Center vertex
                indices.push_back(baseStartIndex);       // First vertex on the circle
                indices.push_back(baseStartIndex + i);   // Last vertex on the circle
            }
        }

        return { std::move(verts), std::move(indices) };
    }


    template <typename VERTEX>
    static IndexedTrigList<VERTEX> Make()
    {
        return MakeTesselated<VERTEX>(40, 40);
    }
};