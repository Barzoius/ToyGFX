#include "VertexArray.h"


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}


VertexArray::~VertexArray()
{

}


void VertexArray::Bind()
{
    glBindVertexArray(ID);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
}


void VertexArray::LinkVertexBuff(VertexBuffer vb)
{
    //vb.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}



GLuint VertexArray::GetID()
{
    return ID;
}