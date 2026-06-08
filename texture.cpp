#include "texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {

    type = texType;

    stbi_set_flip_vertically_on_load(true);
    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load(
        image,
        &widthImg,
        &heightImg,
        &numColCh,
        0
    );
    //error logging
    if(!bytes)
    {
        std::cout << "Failed to load image!" << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }
    else
    {
        std::cout << widthImg << " "
            << heightImg << " "
            << numColCh << std::endl;
    }


    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(type, ID);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(type, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(type);

    stbi_image_free(bytes);
    glBindTexture(type, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    GLuint tex0uni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(tex0uni, unit);
}

void Texture::Bind() {
    glBindTexture(type, ID);
}

void Texture::Unbind() {
    glBindTexture(type, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}