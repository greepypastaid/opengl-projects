#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader Standar Minimal Buat Version 330
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment Shader Standart Minimal Buat Version 330
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // Dapet warna oren dari RGBA
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

    // Buat Jendela Sir ukurannya 1920 x 1200 seukuran layar laptopku!
    GLFWwindow* window = glfwCreateWindow(1920, 1200, "Bikin Segitiga", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // ya kalau gagal langsung terminate
        return -1;
    }
    glfwMakeContextCurrent(window); // fungsi bikin context opengl di jendela itu sir!
    // Beri tahu GLFW yg baru sir fungsi mana yang harus dipanggil kalau ukuran jendela berubah
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
    // Lampirkan kedua shader ke program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Hubungkan program
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Tentukan koordinat 3 titik untuk segitiga
    float vertices[] = {
        -0.2f, -0.4f, 0.0f,  // Titik kiri bawah
         0.2f, -0.4f, 0.0f,  // Titik kanan bawah
         0.0f,  0.4f, 0.0f   // Titik atas
    };

     // Buat dan atur VBO dan VAO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Bind VAO agar semua konfigurasi berikutnya disimpan di VAO ini
    glBindVertexArray(VAO);

    // Bind VBO dan masukkan data titik ke VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Beri tahu OpenGL bagaimana cara membaca data di VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // RENDER LOOP (LOOP UTAMA PROGRAM)
    while (!glfwWindowShouldClose(window)) {
        // Hapus layar dan isi dengan warna
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting warna sir jadi warna biru
        glClear(GL_COLOR_BUFFER_BIT); // Hapus layar belakang dengan warna yang di-set tadi

        // Aktifkan program shader kita
        glUseProgram(shaderProgram);
        // Aktifkan VAO yang berisi semua konfigurasi
        glBindVertexArray(VAO);
        // Perintah untuk menggambar segitiga
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Tukar buffer untuk menampilkan hasil gambar ke layar
        glfwSwapBuffers(window);
        // Periksa dan proses event (seperti klik mouse atau tombol keyboard)
        glfwPollEvents();
    }

    // Kalau udah
    // Hapus semua objek yang kita buat
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Hentikan GLFW
    glfwTerminate();
    return 0;
}
