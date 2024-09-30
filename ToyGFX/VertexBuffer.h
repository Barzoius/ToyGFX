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
    GLuint ID;
    std::vector<float> mVertices;
};