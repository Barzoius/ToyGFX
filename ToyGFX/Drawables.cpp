#include "Drawable.h"
#include "ElementBuffer.h"

#include <cassert>
#include <typeinfo>



void Drawable::Draw() const noexcept
{
    if (pShaderProgram) {
        pShaderProgram->use(); // Ensure the shader program is in use
    }

    for (auto& b : bindables)
    {

        b->Bind();
    }


    glDrawElements(GL_TRIANGLES, (GLsizei)pElemBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, 0);

}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept
{
    bindables.push_back(std::move(bind));
}

void Drawable::AddElementBuffer(std::unique_ptr<ElementBuffer> ibuf) noexcept
{
    assert("Attempting to add index buffer a second time" && pElemBuffer == nullptr);
    pElemBuffer = ibuf.get();
    bindables.push_back(std::move(ibuf));
}

void Drawable::AddShaderProgram(std::unique_ptr<ShaderSuite> ss) noexcept
{
    assert("Attempting to add a second shader program" && pShaderProgram == nullptr);
    pShaderProgram = std::move(ss);

}


ShaderSuite* Drawable::GetShader() const noexcept
{
    return pShaderProgram.get();
}

