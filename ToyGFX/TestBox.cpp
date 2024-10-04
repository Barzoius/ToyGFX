//#include "TestBox.h"
//#include "Cube.h"
//#include "BindableObjects.h"
//#include "Shaders\Shader.h"
//
//#include <string>
//
//TestBox::TestBox(float size)
//{
//    struct VERTEX
//    {
//        glm::vec3 pos;
//    };
//
//    auto model = Cube::Make<VERTEX>();
//
//    model.Treansform(glm::vec3(size, size, size));
//    
//    AddBind(std::make_unique<VertexBuffer>(model.vertices));           // vertices
//    AddBind(std::make_unique<VertexArray>());
//
//    AddElementBuffer(std::make_unique<ElementBuffer>(model.indices));  // indices
//
//    AddShaderProgram(std::make_unique<ShaderSuite>(std::initializer_list<std::pair<std::string_view, Shader::ShaderType>>{
//        {"Shaders/VertShader.glsl", Shader::ShaderType::VERTEX},
//        { "Shaders/FragShader.glsl", Shader::ShaderType::FRAGMENT },
//    }));
//
//}
//
//void TestBox::SetPosition(glm::vec3 pos) noexcept
//{
//    mPos.x = pos.x;
//    mPos.y = pos.y;
//    mPos.z = pos.z;
//
//}
//
//glm::mat4x4 TestBox::GetTransformMatrix() const noexcept
//{
//    // add the rotation
//    return glm::translate(glm::mat4(1.0f), mPos); // * rotation
//}