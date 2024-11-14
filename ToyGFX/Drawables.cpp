#include "Drawable.h"
#include "ElementBuffer.h"

#include <cassert>
#include <typeinfo>

#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"


void Drawable::Draw(glm::mat4& viewMatrix, glm::mat4& projMatrix) const noexcept
{
    if (pShaderProgram) {
        pShaderProgram->use(); 
    }

    glm::mat4 model = this->GetTransformMatrix();

    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -6.0f));


    //MODEL

    unsigned int modelLoc = glGetUniformLocation(this -> GetShader()->GetID(), "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    //VIEW

    unsigned int viewLocBox = glGetUniformLocation(this->GetShader()->GetID(), "view");

    glUniformMatrix4fv(viewLocBox, 1, GL_FALSE, &viewMatrix[0][0]);


    //PROJ

    this->GetShader()->setMat4("projection", projMatrix);


    for (auto& b : bindables)
    {

        b->Bind();
    }

    glDrawElements(GL_TRIANGLES, (GLsizei)pElemBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, 0);


    //for weird circle contour
    //glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)pElemBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, (void*)0); // Draw using indices

    //glDrawElements(GL_QUADS, (GLsizei)pElemBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, (void*)0); // Draw using indices

    //glDrawElements(GL_LINES, (GLsizei)pElemBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, (void*)0); // Draw using indices

    glBindVertexArray(0);

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


void Drawable::DrawIndexed(std::vector<glm::vec3>& translations, glm::mat4& viewMatrix, glm::mat4& projMatrix)
{

    if (pShaderProgram) {
        pShaderProgram->use();
    }

    glm::mat4 model = this->GetTransformMatrix();

    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -6.0f));


    //MODEL

    unsigned int modelLoc = glGetUniformLocation(this->GetShader()->GetID(), "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    //VIEW

    unsigned int viewLocBox = glGetUniformLocation(this->GetShader()->GetID(), "view");

    glUniformMatrix4fv(viewLocBox, 1, GL_FALSE, &viewMatrix[0][0]);


    //PROJ

    this->GetShader()->setMat4("projection", projMatrix);

    for (auto& b : bindables)
    {

        b->Bind();
    }



    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVertexBuffer -> GetID()); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);


    //glDrawElements(GL_TRIANGLES, (GLsizei)pElemBuffer->GetIndiciesCount(), GL_UNSIGNED_INT, 0);

    glDrawElementsInstanced(
        GL_TRIANGLES,                                     
        (GLsizei)pElemBuffer->GetIndiciesCount(),         
        GL_UNSIGNED_INT,                                  
        0,                                               
        (GLsizei)translations.size()                     
    );

    glBindVertexArray(0);

}

//void Drawable::LoadTexture(const char* texturePath)
//{
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    //	Desfasurarea imaginii pe orizontala/verticala in functie de parametrii de texturare;
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//    // Modul in care structura de texeli este aplicata pe cea de pixeli;
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    // Incarcarea texturii si transferul datelor in obiectul textura; 
//    int width, height, nrChannels;
//
//    unsigned char* image = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    glGenerateMipmap(GL_TEXTURE_2D);
//
//    // Eliberarea resurselor
//    stbi_image_free(image);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}

