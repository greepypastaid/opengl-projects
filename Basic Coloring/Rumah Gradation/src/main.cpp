#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader: sekarang menerima posisi (location = 0) dan warna per-vertex (location = 1)
// serta meneruskan warna ke fragment shader.
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor; // kirim ke fragment shader\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = aColor;\n"
    "}\0";

// Fragment Shader: menerima warna interpolated dari vertex shader dan uniform uAlpha untuk transparansi
const char* fragmentShaderSource = "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "uniform float uAlpha; // transparansi dikontrol dari CPU\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, uAlpha);\n"
    "}\n\0";

// Fungsi yang akan dipanggil setiap kali ukuran jendela berubah
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

    // Inisialisasi GLFW
    glfwInit();

    // Setting OpenGL Version 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Buat jendela 800 x 600
    GLFWwindow* window = glfwCreateWindow(800, 600, "Bikin Rumah Gradasi AHAY ASOY", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // --- SHADERS: buat, compile, link (sederhana, tanpa pemeriksaan error panjang) ---
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // --- DATA VERTEX: untuk tiap vertex sediakan posisi (x,y,z) dan warna (r,g,b) ---
    // Struktur tiap vertex: [pos.x, pos.y, pos.z, col.r, col.g, col.b]
    float vertices[] = {
        // Tembok
        // Posisi             // Warna
        0.6f,  0.2f, 0.0f,    0.0f, 1.0f, 0.0f, // 0: Atas kanan
        0.6f, -0.6f, 0.0f,    1.0f, 1.0f, 1.0f, // 1: Bawah kanan
        -0.6f, -0.6f, 0.0f,   0.9f, 1.0f, 0.3f, // 2: Bawah kiri
        -0.6f,  0.2f, 0.0f,   0.0f, 0.1f, 0.5f, // 3: Atas kiri

        // Atap (Warna Cokelat)
        // Posisi             // Warna
        0.0f,  0.7f, 0.0f,    0.6f, 0.5f, 0.7f, // 4: Atap atas
        -0.6f,  0.2f, 0.0f,   0.4f, 0.9f, 0.4f, // 5: Atap kiri bawah (sama dengan titik 3)
        0.6f,  0.2f, 0.0f,    0.2f, 0.1f, 0.21f  // 6: Atap kanan bawah (sama dengan titik 0)    
    };

    unsigned int indices[] = {
        // Indeks untuk Tembok
        0, 1, 2, // Segitiga pertama
        2, 3, 0, // Segitiga kedua
        
        // Indeks untuk Atap
        5, 6, 4  // Atap
    };

    // Buat dan atur VBO dan VAO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind VBO dan kirim data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind EBO dan masukkan data indeks
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atur attribute pointer untuk posisi (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atur attribute pointer untuk warna (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Aktifkan blending supaya alpha pada frag shader berfungsi untuk transparansi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Ambil lokasi uniform uAlpha dari program shader (sekali saja)
    glUseProgram(shaderProgram);
    int alphaLoc = glGetUniformLocation(shaderProgram, "uAlpha");

    // Nilai alpha awal (1.0 = opaque, 0.0 = fully transparent)
    float alpha = 1.0f;

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Simple input untuk mengubah transparansi dengan tombol UP / DOWN
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            alpha += 0.01f;
            if (alpha > 1.0f) alpha = 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            alpha -= 0.01f;
            if (alpha < 0.0f) alpha = 0.0f;
        }

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Gunakan shader dan kirim uniform alpha
        glUseProgram(shaderProgram);
        glUniform1f(alphaLoc, alpha); // set transparansi via uniform

        // Bind VAO dan draw
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Menggambar 6 indeks

        // Swap buffer dan poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
