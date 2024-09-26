#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(std::vector<float>& vertices)
    :
    mVertices(vertices)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), mVertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
}


void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), mVertices.data(), GL_STATIC_DRAW);
}

