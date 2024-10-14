#pragma once

#include "Bindable.h"

class UniformBuffer : public Bindable
{
public:
    UniformBuffer();
    ~UniformBuffer();

    void Bind() override;
    void Unbind() override;

private:

};