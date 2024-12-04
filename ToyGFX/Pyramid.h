#pragma once

#include "IndexedTrigList.h"
#include "Math.h"

class Pyramid
{
public:

    static glm::vec3 GetRandomColor()
    {
        // Generate random float values between 0.0f and 1.0f
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random value for Red
        float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random value for Green
        float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random value for Blue

        return glm::vec3(r, g, b);
    }


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
    static IndexedTrigList<VERTEX> MakePYRColored(int stacks, int sectors)
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
            verts[i].col = GetRandomColor();
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
    static IndexedTrigList<VERTEX> MakeWithNormals(int stacks, int sectors)
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


        std::vector<float> baseCircleNormals;

        float zAngle = atan2(RAD, height);
        float x0 = cos(zAngle);     
        float z0 = sin(zAngle);

        for (int i = 0; i <= sectors; i++)
        {
            float sectorAngle = longitudeAngle * i;
            baseCircleNormals.push_back(cos(sectorAngle) * x0); 
            baseCircleNormals.push_back(sin(sectorAngle) * x0); 
            baseCircleNormals.push_back(z0);

        }

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;

        for (int i = 0; i <= stacks; i++)
        {
            z = -(height * 0.5f) + (float)i / stacks * height;
            radius = RAD * (1.0f - (float)i / stacks);

            for (int j = 0, k = 0; j <= sectors; j++, k += 3)
            {
                x = baseCircle[k];
                y = baseCircle[k + 1];
                vertices.emplace_back(x * radius, y * radius, z);
                normals.emplace_back(glm::vec3(baseCircleNormals[k], 
                                           baseCircleNormals[k+1],
                                           baseCircleNormals[k + 2]));



            }
        }


        //Base vertices

        z = -height * 0.5f;

        vertices.emplace_back(0.0f, 0.0f, z);
        normals.emplace_back(0, 0, -1);
        for (int j = 0, k = 0; j < sectors; j++, k += 3)
        {

            x = baseCircle[k];
            y = baseCircle[k + 1];

            vertices.emplace_back(x * RAD, y * RAD, z);
            normals.emplace_back(0,0,-1);

        }

        


        std::vector<VERTEX> verts(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts[i].pos = vertices[i];
            verts[i].n = normals[i];
           // std::cout << std::endl<< vertices.size() << " " << normals.size();

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
        return MakeTesselated<VERTEX>(1, 20);
    }


    template <typename VERTEX>
    static IndexedTrigList<VERTEX> MakeColored()
    {
        return MakePYRColored<VERTEX>(1, 20);
    }


    template <typename VERTEX>
    static IndexedTrigList<VERTEX> MakeNormaled()
    {
        return MakeWithNormals<VERTEX>(1, 80);
    }
};