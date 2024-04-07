#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#endif

#include <iostream>

// Vertices coordinates
GLfloat vertices[] = { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,         // Lower left corner
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,       // Upper left corner
        0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    // Upper right corner
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,    // Lower right corner
};

// Indices for vertices order
GLuint indices[] = {
        0, 2, 1, // Upper triangle
        0, 3, 2 // Lower triangle
};

const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 400;
int main()
{

    glfwInit();

    // Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initializing a Window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to make window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Loading GLAD
    gladLoadGL();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Shader shaderProgram(
            "resources/shaders/default.vert",
            "resources/shaders/default.frag"
    );

    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    GLuint uniformId = glGetUniformLocation(shaderProgram.id, "scale");

    // Keeping the Window Alive
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        glUniform1f(uniformId, 0.5f);
        vao.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.Delete();

    // Destroy the Window
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
