#pragma once


#include <vector>
#include <memory>

#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Shaders\Shader.h"

#include "VertexBuffer.h"

class Bindable;


class Drawable
{
public:
    Drawable() = default;
    Drawable(const Drawable&) = delete;
    ~Drawable() = default;

    void Draw(glm::mat4& viewMatrix, glm::mat4& projMatrix) const noexcept;


    virtual glm::mat4x4 GetTransformMatrix() const noexcept = 0;

    ShaderSuite* GetShader() const noexcept;

    void LoadTexture(const char* texturePath);

    void DrawIndexed(std::vector<glm::vec3>& translations, glm::mat4& viewMatrix, glm::mat4& projMatrix);

    template <class D>
    void InitInstancedData(std::vector<glm::vec3>& translations)
    {
        instanceVertexBuffer = std::make_unique<VertexBuffer<glm::vec3>>(translations);

        glBindBuffer(GL_ARRAY_BUFFER, instanceVertexBuffer -> GetID());
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * translations.size(), translations.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }



protected:
    void AddBind(std::unique_ptr<Bindable>) noexcept;
    void AddElementBuffer(std::unique_ptr<class ElementBuffer>) noexcept;
    void AddShaderProgram(std::unique_ptr<ShaderSuite>) noexcept;

private:
    std::unique_ptr<class ShaderSuite> pShaderProgram;
    const class ElementBuffer* pElemBuffer = nullptr;

    std::unique_ptr<VertexBuffer<glm::vec3>> instanceVertexBuffer;

    std::vector<std::unique_ptr<Bindable>> bindables;

    GLuint texture;
};