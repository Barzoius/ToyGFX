#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Bindable
{
public:
    virtual void Bind() = 0;
};

