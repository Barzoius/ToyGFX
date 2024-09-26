#include "VertexArray.h"


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &VAO);
}


VertexArray::~VertexArray()
{

}


void VertexArray::Bind()
{
    glBindVertexArray(VAO);
}


void VertexArray::LinkVertexBuff(VertexBuffer vb)
{
    vb.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}



GLuint VertexArray::GetVAO()
{
    return VAO;
}