#pragma once

#include "IndexedTrigList.h"
#include "Math.h"

class CircleContour
{
public:
    template<typename VERTEX>
    static IndexedTrigList<VERTEX> Make()
    {
        constexpr int numSegments = 100;
        constexpr float innerRadius = 1.0f; 
        constexpr float outerRadius = 2.0f;


        std::vector<glm::vec3> innerVertices(numSegments);
        std::vector<glm::vec3> outerVertices(numSegments);

        std::vector<glm::vec3> contourVertices(2 * numSegments);


        for (int i = 0; i < numSegments; i++) {
            float theta = (2.0f * FPI * i) / (numSegments-1);
            innerVertices[i] = glm::vec3(innerRadius * cos(theta), innerRadius * sin(theta), 0.0f);
            outerVertices[i] = glm::vec3(outerRadius * cos(theta), outerRadius * sin(theta), 0.0f);
        }

        for (int i = 0; i < numSegments; i++) {
 
            contourVertices[i] = innerVertices[i]; 
            contourVertices[i + numSegments] = outerVertices[i];
        }


        std::vector<VERTEX> verts(contourVertices.size());

        for (size_t i = 0; i < contourVertices.size(); i++)
        {
            verts[i].pos = contourVertices[i];
        }

        std::vector<unsigned int> indices(2 * numSegments);

        for (int i = 0; i < numSegments - 1; i++) {
           
            indices[2 * i] = i; 
            indices[2 * i + 1] = i + numSegments; 
        }

        indices[2 * (numSegments - 1)] = numSegments - 1;
        indices[2 * (numSegments - 1) + 1] = numSegments; 

        return{
            std::move(verts), std::move(indices)
        };
    }
};