#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Vertex Shader dengan texture coordinates
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = aColor;\n"
    "   TexCoord = aTexCoord;\n"
    "}\0";

// Fragment Shader dengan texture
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D ourTexture;\n"
    "uniform float intensity;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(ourTexture, TexCoord);\n"
    "}\n\0";

// Fungsi yang akan dipanggil setiap kali ukuran jendela berubah
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

    // Inisialisasi GLFW WAJIBUUNN
    glfwInit();

    // Setting OpenGL Version 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Pakai Core Profile, yang artinya tidak pakai fungsi-fungsi lama
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Buat Jendela Sir ukurannya 800 x 800 seukuran layar laptopku!
    GLFWwindow* window = glfwCreateWindow(800, 800, "BAHLULL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // BIKIN GLAD SIR (buat memuat semua fungsi OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Buat objek Vertex Shader dan kompilasi kodenya
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Buat objek Fragment Shader dan kompilasi kodenya
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Buat program shader
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        // Posisi           // Warna           // Texture Coords
        -0.8f,  0.8f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // Kiri Atas
         0.8f,  0.8f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // Kanan Atas
         0.8f, -0.8f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // Kanan Bawah
        -0.8f, -0.8f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Kiri Bawah
    };

    unsigned int indices[] = { 
        0, 1, 2,
        2, 3, 0,
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);  // buat flip gambar
    int width, height, nrChannels;
    // Paksa load sebagai RGB (3 channels)
    unsigned char *data = stbi_load("D:\\Kuliah\\Semester 5\\Grafika Komputer\\Basic Coloring\\Persegi Textured\\bahlilkecil.jpg", &width, &height, &nrChannels, 3);
    if (data) {
        // Selalu gunakan RGB format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        std::cout << "Texture loaded successfully! Width: " << width << " Height: " << height << " Channels: " << nrChannels << std::endl;
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shaderProgram);
        
        float intensity = 1.0f;
        int intensityLocation = glGetUniformLocation(shaderProgram, "intensity");
        glUniform1f(intensityLocation, intensity);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
