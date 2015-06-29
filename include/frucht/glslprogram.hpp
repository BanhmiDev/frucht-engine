#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

namespace Frucht {

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
    void linkShaders();
    void addAttribute(const std::string& attributeName);
   
    GLint getUniformLocation(const std::string& uniformName);

    void use();
    void unuse();
private:
    void compileShader(const std::string& filePath, GLuint id);

    int m_numAttributes;
    
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};

}

#endif // GLSLPROGRAM_H
