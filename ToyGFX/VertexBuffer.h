#pragma once

#include "Bindable.h"

#include <vector>

class VertexBuffer : public Bindable
{
public:
    VertexBuffer(std::vector<float>& vertices);
    ~VertexBuffer();

    void Bind() override;


private:
    GLuint VBO;
    std::vector<float> mVertices;
};