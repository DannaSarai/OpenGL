#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Funciones para la ventana de GLFW
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Configuración de la ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// Vertex shader que transforma posicion y atributos para preparar el renderizado 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Determina el color final de cada pixel
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.6f, 0.2f, 0.8f, 1.0f);\n"
"}\n\0";

int main()
{
    // Configuración e inicialización de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // Creación de la ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Danna Morales - 1750712265", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compilación y enlazado de los shaders
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Se verifican si es que existen errores en el vertex shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Se crean los shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Se verifica si existen errores en el enlazado
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Elimina los shaders una vez ya se enlazan al programa
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Se configuran los datos de los vertices y buffers 
    float vertices[] = {
         0.25f, 0.43f, 0.0f,
         -0.25f, 0.43f, 0.0f,
         -0.5f,  0.0f, 0.0f,
         -0.25f, -0.43f, 0.0f,
         0.25f, -0.43f, 0.0f,
         0.5f, 0.0f, 0.0f
    };

    // Se crean los objetos de vértices
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    // Se copian los datos de vertices en el buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Se configuran los atributos de vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Se desvincula el VBO y el VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Se crea un bucle de renderizado
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(0.9f, 0.6f, 0.8f, 1.0f); // color de fondo
        glClear(GL_COLOR_BUFFER_BIT);

        // Se dibuja el triangulo
        glUseProgram(shaderProgram); // Se activan los shaders
        glBindVertexArray(VAO); // Se vincula el VAO
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6); // Se dibujan 6 vértices

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Se limpian los recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Se termina el GLFW
    glfwTerminate();
    return 0;
}

// Función que procesa la entrada del teclado
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Función para redimensionar la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Se ajusta el viewport al nuevo tamaño de la ventana
    glViewport(0, 0, width, height);
}