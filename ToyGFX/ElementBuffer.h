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

    size_t GetIndiciesCount() const;

private:
    GLuint ID;
    std::vector<unsigned int> indices;

    size_t mIndiciesCount;
};