#include "TestSquare.h"
#include "Square.h"


#include "BindableObjects.h"
#include "Shaders\Shader.h"

TestSquare::TestSquare()
{
    struct VERTEX
    {
        glm::vec3 pos;
        glm::vec3 col;
    };

    auto model = Square::Make<VERTEX>();

    AddBind(std::make_unique<VertexBuffer<VERTEX>>(model.vertices));           // vertices
    AddBind(std::make_unique<VertexArray>());

    AddElementBuffer(std::make_unique<ElementBuffer>(model.indices));  // indices

    AddShaderProgram(std::make_unique<ShaderSuite>(std::initializer_list<std::pair<std::string_view, Shader::ShaderType>>{
        {"Shaders/VertShader.glsl", Shader::ShaderType::VERTEX},
        { "Shaders/FragShader.glsl", Shader::ShaderType::FRAGMENT },
    }));

}

glm::mat4x4 TestSquare::GetTransformMatrix() const noexcept
{
    return glm::mat4(1.0f);
}