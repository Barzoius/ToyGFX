#pragma once

#include "Bindable.h"
#include "VertexBuffer.h"


class VertexArray : Bindable
{
public:

    VertexArray();
    ~VertexArray();

    void Bind() override;

    void LinkVertexBuff(VertexBuffer vb);

    GLuint GetVAO();
private:
    GLuint VAO;
};