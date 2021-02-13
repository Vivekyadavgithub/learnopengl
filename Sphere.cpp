#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1920, 1080, "opengl", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error\n";
    }

    std::vector<float> vertices;
    std::vector<unsigned> indices;
    int indicator = 0;

    for(int i = 0 ; i <= 40 ; i++)
    {
        double lat0 = glm::pi<double>() * (-0.5 + (double) (i - 1) / 40);
               double z0  = sin(lat0);
               double zr0 =  cos(lat0);

               double lat1 = glm::pi<double>() * (-0.5 + (double) i / 40);
               double z1 = sin(lat1);
               double zr1 = cos(lat1);

               for(int j = 0; j <= 40 ; j++) {
                   double lng = 2 * glm::pi<double>() * (double) (j - 1) / 40;
                   double x = cos(lng);
                   double y = sin(lng);

                   vertices.push_back(x * zr0);
                   vertices.push_back(y * zr0);
                   vertices.push_back(z0);
                   indices.push_back(indicator);
                   indicator++;

                   vertices.push_back(x * zr1);
                   vertices.push_back(y * zr1);
                   vertices.push_back(z1);
                   indices.push_back(indicator);
                   indicator++;
               }
               indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    }
    unsigned vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned vertex;
    glGenBuffers(1, &vertex);
    glBindBuffer(GL_ARRAY_BUFFER, vertex);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    unsigned index;
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, &indices[0], GL_STATIC_DRAW);

    const char* vertexShaderSource =
        R"GLSL(#version 120
        // Input vertex data, different for all executions of this shader.
        attribute vec3 vertexPosition_modelspace;

        // Output data ; will be interpolated for each fragment.
        varying vec2 UV;

        uniform mat4 projMatrix;
        uniform mat4 mvMatrix;

        void main()
        {
            gl_Position =  vec4(vertexPosition_modelspace, 1);
        })GLSL";

    const char* fragmentShaderSource =
        R"GLSL(#version 330

        void main(){
            // Output color = color of the texture at the specified UV
            gl_FragColor = vec4 (1.0, 0.0, 0.0, 1.0);
        })GLSL";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);


    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glValidateProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_QUAD_STRIP, indices.size(), GL_UNSIGNED_INT, NULL);
        glfwSwapBuffers(window);
        // check and call events and swap the buffers
        glfwPollEvents();
    }
}

