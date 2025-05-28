#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_s.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // Se configura e inicializa el GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // Creación de ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Danna Morales 1750712265", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: carga las funciones de OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // construye y compila los shaders
    Shader ourShader("shaders/b1p2_vertex.vs", "shaders/b1p2_fragment.fs");

    // configurar datos de vértices,búfers y configurar atributos de vértices
    float vertices[] = {
        // posición           // color
        -0.88f, 0.39f, 0.0f,  1.0f, 0.0f, 0.0f,  // H
        -0.64f, 0.62f, 0.0f,  1.0f, 0.0f, 0.0f,  // J
        -0.41f, 0.38f, 0.0f,  1.0f, 0.0f, 0.0f,   // I
        -0.65f, 0.15f, 0.0f,  1.0f, 0.0f, 0.0f,  // G

        -0.63f, -0.81f, 0.0f,  0.6f, 0.1f, 0.9f,  // L
        -0.39f, -0.56f, 0.0f,  0.6f, 0.1f, 0.9f,  // O 
         0.05f, -0.56f, 0.0f,  0.6f, 0.1f, 0.9f,  // N
        -0.15f, -0.8f,  0.0f,  0.6f, 0.1f, 0.9f,  // M

        -0.2f, 0.4f,  0.0f,  0.0f, 0.0f, 1.0f,  // C
        0.27f, 0.39f, 0.0f,  0.0f, 0.0f, 1.0f,  // D
        0.03f, 0.15f, 0.0f,  0.0f, 0.0f, 1.0f,  // E

         0.03f, 0.15f,  0.0f,  0.5f, 0.9f, 0.5f,  // E
        -0.65f, 0.15f,  0.0f,  0.5f, 0.9f, 0.5f,  // G
        -0.31f, -0.19f, 0.0f,  0.5f, 0.9f, 0.5f,  // F
        
        -0.65f,  0.15f,  0.0f,  0.9f, 0.9f, 0.1f,  // G
        -0.17f, -0.33f,  0.0f,  0.9f, 0.9f, 0.1f,  // K 
        -0.63f, -0.81f,  0.0f,  0.9f, 0.9f, 0.1f,  // L 

        -0.39f, -0.56f,  0.0f,  0.0f, 0.5f, 0.2f,  // O
         0.1f,  -0.07f,  0.0f,  0.0f, 0.5f, 0.2f,  // Q
         0.58f, -0.55f,  0.0f,  0.0f, 0.5f, 0.2f,  // P

        0.4f,  -0.55f,  0.0f,  1.0f, 0.5f, 0.0f,  // T
        0.86f, -0.55f,  0.0f,  1.0f, 0.5f, 0.0f,  // R
        0.63f, -0.8f,   0.0f,  1.0f, 0.5f, 0.0  // S

    };

    //EBO_ADD
    unsigned int indices[] = {
      1, 0, 3,  
      1, 2, 3,   
      4, 5, 6,
      4, 7, 6,
      8, 9, 10,
      12, 11, 13,
      14, 15, 16,
      17, 18, 19,
      20, 21, 22
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO); 
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //EBO_ADD
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

        // color en el tiempo
        float timeValue = glfwGetTime();
        ourShader.setFloat("timeValue", timeValue);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
