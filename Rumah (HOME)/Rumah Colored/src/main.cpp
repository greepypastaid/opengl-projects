#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader Standar Minimal Buat Version 330
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n" // Buat input warna cuy wajib!
    "out vec3 ourColor;\n" // Output warna ke arah fragment shader
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = aColor;\n" // ini kode warna ke fragment shader
    "}\0";

// Fragment Shader Standart Minimal Buat Version 330
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n" // Terima warna dari vertex shader
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n" // Dapet warna dari kode yang dibikin dari vertice dibawah sir + paling belang itu adalah A dri RGBA
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
    GLFWwindow* window = glfwCreateWindow(800, 800, "Bikin Rumah", NULL, NULL);
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

    float vertices[] = {
        // Tembok (Warna Putih)
        // Posisi             // Warna
        0.6f,  0.2f, 0.0f,    1.0f, 1.0f, 1.0f, // 0: Atas kanan
        0.6f, -0.6f, 0.0f,    1.0f, 1.0f, 1.0f, // 1: Bawah kanan
        -0.6f, -0.6f, 0.0f,   1.0f, 1.0f, 1.0f, // 2: Bawah kiri
        -0.6f,  0.2f, 0.0f,   1.0f, 1.0f, 1.0f, // 3: Atas kiri

        // Atap (Warna Cokelat)
        // Posisi             // Warna
        0.0f,  0.7f, 0.0f,    0.6f, 0.3f, 0.1f, // 4: Atap atas
        -0.6f,  0.2f, 0.0f,   0.6f, 0.3f, 0.1f, // 5: Atap kiri bawah (sama dengan titik 3)
        0.6f,  0.2f, 0.0f,    0.6f, 0.3f, 0.1f  // 6: Atap kanan bawah (sama dengan titik 0)
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
    
    // Bind VAO agar semua konfigurasi berikutnya disimpan di VAO ini
    glBindVertexArray(VAO);

    // Bind VBO dan masukkan data titik ke VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind EBO dan masukkan data indeks
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atur atribut titik pada location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atur atribut titik pada location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    // RENDER LOOP (LOOP UTAMA PROGRAM)
    while (!glfwWindowShouldClose(window)) {
        // Hapus layar dan isi dengan warna
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Setting warna sir jadi warna biru
        glClear(GL_COLOR_BUFFER_BIT); // Hapus layar belakang dengan warna yang di-set tadi

        // Aktifkan program shader kita
        glUseProgram(shaderProgram);
        // Aktifkan VAO yang berisi semua konfigurasi
        glBindVertexArray(VAO); // Pastikan VAO terikat
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Menggambar 6 indeks

        // Tukar buffer untuk menampilkan hasil gambar ke layar
        glfwSwapBuffers(window);
        // Periksa dan proses event (seperti klik mouse atau tombol keyboard)
        glfwPollEvents();
    }

    // Kalau udah
    // Hapus semua objek yang kita buat
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Hentikan GLFW
    glfwTerminate();
    return 0;
}
