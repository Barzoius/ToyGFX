#pragma once

#include "Drawable.h"
#include "ElementBuffer.h"

class TestPlane : public Drawable
{
public:
    TestPlane(float size);

    void SetPosition(glm::vec3 pos) noexcept;

    glm::mat4x4 GetTransformMatrix() const noexcept override;


private:
    glm::vec3 mPos = glm::vec3(1.0f, 1.0f, 1.0f);

};