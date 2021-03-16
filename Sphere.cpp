#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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

  //  Assimp::Importer importer;
    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    /*float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };*/

    /*float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };*/

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    float PI = 3.14f;
    float stackCount = 100;
    float sectorCount = 100;
    int radius = 1;
    std::vector<float>vertices;
    std::vector<float>normals;
    std::vector<float>texCoords;

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back(s);
            texCoords.push_back(t);
        }
    }
/*
    std::vector<float> vertices = { 0.000796274,
            0,
            1,
            0.000644348,
            0.000467833,
            1,
            0.000246545,
            0.000757145,
            1,
            -0.000245339,
            0.000757537,
            1,
            -0.000643603,
            0.000468859,
            1,
            -0.000796273,
            1.26811e-06,
            1,
            -0.000645093,
            -0.000466806,
            1,
            -0.00024775,
            -0.000756751,
            1,
            0.000244132,
            -0.000757926,
            1,
            0.000642855,
            -0.000469883,
            1,
            0.00079627,
            -2.53621e-06,
            1,
            0.309623,
            0,
            0.950859,
            0.250548,
            0.181912,
            0.950859,
            0.0958663,
            0.294408,
            0.950859,
            -0.0953973,
            0.29456,
            0.950859,
            -0.250258,
            0.182311,
            0.950859,
            -0.309622,
            0.000493089,
            0.950859,
            -0.250837,
            -0.181513,
            0.950859,
            -0.0963351,
            -0.294255,
            0.950859,
            0.0949281,
            -0.294712,
            0.950859,
            0.249967,
            -0.182709,
            0.950859,
            0.309621,
            -0.000986177,
            0.950859,
            0.588172,
            0,
            0.808736,
            0.475951,
            0.345567,
            0.808736,
            0.182111,
            0.559269,
            0.808736,
            -0.18122,
            0.559558,
            0.808736,
            -0.4754,
            0.346325,
            0.808736,
            -0.588171,
            0.000936692,
            0.808736,
            -0.476501,
            -0.344809,
            0.808736,
            -0.183002,
            -0.558978,
            0.808736,
            0.180329,
            -0.559846,
            0.808736,
            0.474848,
            -0.347081,
            0.808736,
            0.588169,
            -0.00187338,
            0.808736,
            0.809204,
            0,
            0.587528,
            0.654811,
            0.47543,
            0.587528,
            0.250548,
            0.76944,
            0.587528,
            -0.249322,
            0.769837,
            0.587528,
            -0.654053,
            0.476472,
            0.587528,
            -0.809203,
            0.0012887,
            0.587528,
            -0.655568,
            -0.474386,
            0.587528,
            -0.251773,
            -0.769039,
            0.587528,
            0.248096,
            -0.770234,
            0.587528,
            0.653294,
            -0.477513,
            0.587528,
            0.8092,
            -0.00257739,
            0.587528,
            0.951106,
            0,
            0.308865,
            0.769639,
            0.558801,
            0.308865,
            0.294484,
            0.904368,
            0.308865,
            -0.293043,
            0.904836,
            0.308865,
            -0.768748,
            0.560026,
            0.308865,
            -0.951105,
            0.00151468,
            0.308865,
            -0.770528,
            -0.557574,
            0.308865,
            -0.295924,
            -0.903898,
            0.308865,
            0.291602,
            -0.905301,
            0.308865,
            0.767855,
            -0.561249,
            0.308865,
            0.951101,
            -0.00302936,
            0.308865,
            1,
            0,
            -5.24521e-08,
            0.809204,
            0.587528,
            -5.24521e-08,
            0.309623,
            0.950859,
            -5.24521e-08,
            -0.308108,
            0.951351,
            -5.24521e-08,
            -0.808267,
            0.588816,
            -5.24521e-08,
            -0.999999,
            0.00159255,
            -5.24521e-08,
            -0.810139,
            -0.586238,
            -5.24521e-08,
            -0.311137,
            -0.950365,
            -5.24521e-08,
            0.306593,
            -0.951841,
            -5.24521e-08,
            0.807329,
            -0.590102,
            -5.24521e-08,
            0.999995,
            -0.00318509,
            -5.24521e-08,
            0.951106,
            0,
            -0.308866,
            0.769639,
            0.558801,
            -0.308866,
            0.294484,
            0.904368,
            -0.308866,
            -0.293043,
            0.904836,
            -0.308866,
            -0.768748,
            0.560026,
            -0.308866,
            -0.951105,
            0.00151468,
            -0.308866,
            -0.770528,
            -0.557574,
            -0.308866,
            -0.295924,
            -0.903898,
            -0.308866,
            0.291602,
            -0.905301,
            -0.308866,
            0.767855,
            -0.561249,
            -0.308866,
            0.951101,
            -0.00302936,
            -0.308866,
            0.809204,
            0,
            -0.587528,
            0.654811,
            0.47543,
            -0.587528,
            0.250548,
            0.769439,
            -0.587528,
            -0.249322,
            0.769837,
            -0.587528,
            -0.654053,
            0.476472,
            -0.587528,
            -0.809203,
            0.0012887,
            -0.587528,
            -0.655568,
            -0.474386,
            -0.587528,
            -0.251773,
            -0.769039,
            -0.587528,
            0.248096,
            -0.770234,
            -0.587528,
            0.653294,
            -0.477513,
            -0.587528,
            0.8092,
            -0.00257739,
            -0.587528,
            0.588172,
            0,
            -0.808736,
            0.475951,
            0.345567,
            -0.808736,
            0.182111,
            0.559269,
            -0.808736,
            -0.18122,
            0.559558,
            -0.808736,
            -0.4754,
            0.346325,
            -0.808736,
            -0.588171,
            0.000936692,
            -0.808736,
            -0.476501,
            -0.344809,
            -0.808736,
            -0.183002,
            -0.558978,
            -0.808736,
            0.180329,
            -0.559846,
            -0.808736,
            0.474848,
            -0.347081,
            -0.808736,
            0.588169,
            -0.00187338,
            -0.808736,
            0.309623,
            0,
            -0.950859,
            0.250548,
            0.181912,
            -0.950859,
            0.0958663,
            0.294408,
            -0.950859,
            -0.0953973,
            0.29456,
            -0.950859,
            -0.250258,
            0.182311,
            -0.950859,
            -0.309622,
            0.000493089,
            -0.950859,
            -0.250837,
            -0.181513,
            -0.950859,
            -0.0963351,
            -0.294255,
            -0.950859,
            0.0949281,
            -0.294712,
            -0.950859,
            0.249967,
            -0.182709,
            -0.950859,
            0.309621,
            -0.000986177,
            -0.950859,
            0.000796274,
            0,
            -1,
            0.000644348,
            0.000467833,
            -1,
            0.000246545,
            0.000757145,
            -1,
            -0.000245339,
            0.000757537,
            -1,
            -0.000643603,
            0.000468859,
            -1,
            -0.000796273,
            1.26811e-06,
            -1,
            -0.000645093,
            -0.000466806,
            -1,
            -0.00024775,
            -0.000756751,
            -1,
            0.000244132,
            -0.000757926,
            -1,
            0.000642855,
            -0.000469883,
            -1,
            0.00079627,
            -2.53621e-06,
            -1 };*/
    /*float position[] = {
     0.5f/2.0f,  0.5f/2.0f, 0.0f/2.0f,  // top right
     0.5f/2.0f, -0.5f/2.0f, 0.0f/2.0f,  // bottom right
    -0.5f/2.0f, -0.5f/2.0f, 0.0f/2.0f,  // bottom left
    -0.5f/2.0f,  0.5f/2.0f, 0.0f,   // top left
     1.0f     ,  1.0f     , 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle
    };
    float texCoords[] = {
            0.0f, 0.0f,  // lower-left corner
            1.0f, 0.0f,  // lower-right corner
            0.5f, 1.0f   // top-center corner
    };*/


    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        //"layout(location = 1) in vec3 aColor;\n"
        "layout(location = 1) in vec2 aTexCoord;\n"
        //"out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        // "uniform mat4 transform;\n"
        "uniform mat4 model;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "void main()\n"
        "{\n"
        "gl_Position = projection * view * model  * vec4(aPos, 1.0f);\n"
        //"ourColor = aColor;\n"
        "TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        //"in vec3 ourColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "void main()\n"
        "{\n"
        "   FragColor = /*texture(ourTexture, TexCoord) * */vec4(0.0, 1.0, 1.0, 1.0);\n"
        "}\n";

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBuffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*4, (void*)&vertices[0], GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, 8 * sizeof(unsigned), 0);
    //glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    /*unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned), indices, GL_STATIC_DRAW);*/



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

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

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
   // ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    // 0. copy our vertices array in a buffer for OpenGL to use
    /*glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);*/
    // 3. now draw the object
    //someOpenGLFunctionThatDrawsOurTriangle();
    //float timeValue = glfwGetTime();
    //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    //glUseProgram(shaderProgram);
    //glUseProgram(shaderProgram);
    //float timeValue = glfwGetTime();
    //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    // Setup Dear ImGui context



    bool demoWindow = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    std::vector<glm::vec3>boxes;
    float pos = 0.5f;
    float angle = 2.0f;
    bool shape = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();
       // ImGui_ImplOpenGL3_NewFrame();
       // ImGui_ImplGlfw_NewFrame();
        // be sure to activate the shader before any calls to glUniform
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        // const float radius = 10.0f;
        // float camX = sin(glfwGetTime()) * radius;
         //float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::scale(trans, glm::vec3(0.3, 0.3, 0.3));
        //trans = glm::rotate(trans, /*(float)glfwGetTime() **/ glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        //unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)700 / (float)700, 0.1f, 100.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        unsigned int projection_loc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));
        unsigned int view_loc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 1; i++)
        {
            //glm::mat4 transform = glm::mat4(1.0f);
            //transform = glm::scale(transform, glm::vec3(1.5f, 1.0f, 1.0f));
            //unsigned int transform_loc = glGetUniformLocation(shaderProgram, "transform");
            //glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                scale += 0.02f;
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                scale -= 0.02f;
            }
            model = glm::scale(model, scale);

            unsigned int postions_loc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(postions_loc, 1, GL_FALSE, glm::value_ptr(model));
            if(shape == 0) glDrawArrays(GL_LINE_LOOP, 0, (vertices.size()*4)/12);
            else glDrawArrays(GL_POINTS, 0, (vertices.size()*4) / 12);

            {
                static float f = 0.0f;
                static int counter = 0;
                ImGui::Text("hello world");
                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
                ImGui::ColorEdit3("clear color", (float*)&clear_color);
                ImGui::Checkbox("demo window", &demoWindow);
                ImGui::Checkbox("another window", &show_another_window);

                if (ImGui::Button("Button")) {
                    //boxes.push_back({ pos, 0.0f, 0.0f });
                    shape = !shape;

                }
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);
                ImGui::Text("Application avg %f ms/frame ()", f++);
            }
            for (auto it : boxes) {
                model = glm::translate(model, it);
                glUniformMatrix4fv(postions_loc, 1, GL_FALSE, glm::value_ptr(model));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        ImGui::Render();

        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        // check and call events and swap the buffers
        glfwPollEvents();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    stbi_image_free(data);
    glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &index_buffer);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
   // glViewport(0, 0, width, height);
}
