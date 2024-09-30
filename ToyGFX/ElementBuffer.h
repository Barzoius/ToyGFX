#pragma once

#include "Bindable.h"
#include <vector>

class ElementBuffer : public Bindable
{
public:
    ElementBuffer(std::vector<unsigned int>& idices);
    ~ElementBuffer();

    void Bind() override;

    void DrawIndexed();

    GLuint GetID();

    int GetIndiciesCount();

private:
    GLuint ID;
    std::vector<unsigned int> indices;

    int mIndiciesCount;
};