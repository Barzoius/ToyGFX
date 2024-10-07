#pragma once

#include "Drawable.h"
#include "ElementBuffer.h"

class TestSphere : public Drawable
{
public:
    TestSphere(float size);
    void SetPosition(glm::vec3 pos) noexcept;
    //void SetRotation() noexcept;

    glm::mat4x4 GetTransformMatrix() const noexcept override;

    //void ControlWND() noexcept;

private:
    glm::vec3 mPos = glm::vec3(1.0f, 1.0f, 1.0f);
}; 
