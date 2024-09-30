#pragma once


#include <vector>
#include <memory>

#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Bindable;
class ShaderSuite;

class Drawable
{
public:
    Drawable() = default;
    Drawable(const Drawable&) = delete;
    ~Drawable() = default;

    void Draw() const noexcept;

    virtual glm::mat4x4 GetTransform() const noexcept = 0;
    virtual void Update() noexcept = 0;

protected:
    void AddBind(std::unique_ptr<Bindable>) noexcept;
    void AddElementBuffer(std::unique_ptr<class ElementBuffer>) noexcept;

private:
    const class ShaderSuite* pShaderProgram = nullptr;
    const class ElementBuffer* pElemBuffer = nullptr;

    std::vector<std::unique_ptr<Bindable>> bindables;
};