#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "FactoryOpenGl.h"
#include "IShader.h"
#include "ITransformer.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MineSweeper", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    IFactory* factory = new FactoryOpenGl();
    IShader* shader = factory->makeShader("./shaders/vertex/default.vs", "./shaders/fragment/default.frag");

    GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,      // Верхний правый угол
        0.5f, -0.5f, 0.0f,      // Нижний правый угол
        -0.5f, -0.5f, 0.0f,     // Нижний левый угол
        -0.5f,  0.5f, 0.0f      // Верхний левый угол
    };
    GLuint indices[] = {
        0, 1, 3,    // Первый треугольник
        1, 2, 3     // Второй треугольник
    };

    GLuint VAO;
    GLuint EBO;
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (glfwWindowShouldClose(window) == 0) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ITransformer* transformer = factory->makeTransformer();
        transformer->rotate(45.0f, { 0.0f, 0.0f, 1.0f });
        transformer->scale({ 0.5f, 0.5f, 0.5f });

        shader->use();
        shader->setUniform("ourColor", 0.0f, 1.0f, 0.0f, 1.0f);
        shader->setUniform("transform", transformer);
        delete transformer;

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
