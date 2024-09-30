#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(std::vector<unsigned int>& indices)
    : 
    indices(indices),
    mIndiciesCount(indices.size())
      
{
    glGenBuffers(1, &ID);
}

ElementBuffer::~ElementBuffer()
{

}


void ElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
}



void ElementBuffer::DrawIndexed()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


GLuint ElementBuffer::GetID()
{
    return ID;
}

int ElementBuffer::GetIndiciesCount()
{
    return mIndiciesCount;
}

