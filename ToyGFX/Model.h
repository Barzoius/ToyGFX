#pragma once
#include "Drawable.h"

class Model : public Drawable
{
public:
    Model();

    void CreateMesh(const char* filePath);
};