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
    "in vec3 ourColor;\n"
    "uniform float intensity;\n" // Deklarasi uniform float intensity
    "void main()\n"
    "{\n"
    "   vec3 adjustedColor = ourColor * intensity;\n" // Tambahin intensity sir buat A pada RGBA
    "   FragColor = vec4(adjustedColor, 1.0f);\n"
    "}\n\0";

// Fungsi yang akan dipanggil setiap kali ukuran jendela berubah
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Bikin fungsi konversi dari desain ke opengl X dan Y
float convertX(float designX, float canvasWidth) {
    return (2.0f * designX / canvasWidth) - 1.0f;
}

float convertY(float designY, float canvasHeight) {
    return 1.0f - (2.0f * designY / canvasHeight);
}

float convertColor(int colorValue) {
    return colorValue / 255.0f;
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
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "WOLF IMAGE OPENGL", NULL, NULL);
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

    // Deklarasi dlu cok buat ukuran canvas di digma, canpa, atau yang laen
    float canvasWidth = 1000.0f; // Kataku canvasnya segini bae
    float canvasHeight = 1000.0f; // Nah ini juga

    float designCoords[] = {
        // Formatnya x,y,r,g,b yah gengs!
        330.0f, 469.5f, 255.0f, 255.0f, 255.0f, // 0
        282.0f, 469.5f, 255.0f, 255.0f, 255.0f, // 1
        171.0f, 395.0f, 255.0f, 255.0f, 255.0f, // 2
        343.0f, 348.0f, 255.0f, 255.0f, 255.0f, // 3
        452.0f, 392.5f, 255.0f, 255.0f, 255.0f, // 4
        511.5f, 283.5f, 255.0f, 255.0f, 255.0f, // 5
        452.0f, 250.5f, 255.0f, 255.0f, 255.0f, // 6
        556.5f, 280.0f, 255.0f, 255.0f, 255.0f, // 7
        598.0f, 250.5f, 255.0f, 255.0f, 255.0f, // 8
        507.0f, 334.0f, 255.0f, 255.0f, 255.0f, // 9
        558.5f, 338.0f, 255.0f, 255.0f, 255.0f, // 10
        578.5f, 286.0f, 255.0f, 255.0f, 255.0f, // 11
        608.5f, 286.0f, 255.0f, 255.0f, 255.0f, // 12
        730.5f, 217.0f, 255.0f, 255.0f, 255.0f, // 13
        761.0f, 163.0f, 255.0f, 255.0f, 255.0f, // 14
        783.5f, 167.0f, 255.0f, 255.0f, 255.0f, // 15
        789.5f, 184.5f, 255.0f, 255.0f, 255.0f, // 16
        738.5f, 233.5f, 255.0f, 255.0f, 255.0f, // 17
        816.5f, 241.0f, 255.0f, 255.0f, 255.0f, // 18
        781.5f, 237.11f, 255.0f, 255.0f, 255.0f, // 19
        814.0f, 281.5f, 255.0f, 255.0f, 255.0f, // 20
        791.12f, 267.5f, 255.0f, 255.0f, 255.0f, // 21
        787.5f, 297.0f, 255.0f, 255.0f, 255.0f, // 22
        771.0f, 247.5f, 255.0f, 255.0f, 255.0f, // 23
        657.5f, 361.0f, 255.0f, 255.0f, 255.0f, // 24
        653.0f, 392.5f, 255.0f, 255.0f, 255.0f, // 25
        698.0f, 373.5f, 255.0f, 255.0f, 255.0f, // 26
        712.5f, 335.5f, 255.0f, 255.0f, 255.0f, // 27
        738.0f, 370.5f, 255.0f, 255.0f, 255.0f, // 28
        744.0f, 321.5f, 255.0f, 255.0f, 255.0f, // 29
        756.0f, 369.5f, 255.0f, 255.0f, 255.0f, // 30
        768.0f, 310.5f, 255.0f, 255.0f, 255.0f, // 31
        759.1f, 286.5f, 255.0f, 255.0f, 255.0f, // 32
        779.0f, 367.5f, 255.0f, 255.0f, 255.0f, // 33
        792.0f, 319.0f, 255.0f, 255.0f, 255.0f, // 34
        806.0f, 332.5f, 255.0f, 255.0f, 255.0f, // 35
        814.0f, 363.5f, 255.0f, 255.0f, 255.0f, // 36
        703.0f, 360.5f, 255.0f, 255.0f, 255.0f, // 37
        814.0f, 400.5f, 255.0f, 255.0f, 255.0f, // 38
        799.9f, 383.5f, 255.0f, 255.0f, 255.0f, // 39
        712.9f, 448.5f, 255.0f, 255.0f, 255.0f, // 40
        768.5f, 407.5f, 255.0f, 255.0f, 255.0f, // 41
        703.0f, 415.0f, 255.0f, 255.0f, 255.0f, // 42
        626.5f, 439.5f, 255.0f, 255.0f, 255.0f, // 43
        665.0f, 464.5f, 255.0f, 255.0f, 255.0f, // 44
        584.0f, 468.5f, 255.0f, 255.0f, 255.0f, // 45
        558.5f, 500.5f, 255.0f, 255.0f, 255.0f, // 46
        558.5f, 551.5f, 255.0f, 255.0f, 255.0f, // 47
    };

    // Hitung coy buat jumlah titik yang udah dibuat
    int numVertices = sizeof(designCoords) / sizeof(float) / 5;

    float vertices[numVertices * 6]; // kenapa 6? karena designCoord cuman x,y,z,r,g,b

    // Bikin looping konversi
    for (int i = 0; i < numVertices; i++) {
        int designIndex = i * 5;     // Index di designCoords (x,y,r,g,b = 5 float)
        int vertexIndex = i * 6;     // Index di vertices (x,y,z,r,g,b = 6 float)

        // Konversi X dan Y dari desain ke OpenGL
        vertices[vertexIndex + 0] = convertX(designCoords[designIndex + 0], canvasWidth);      // X
        vertices[vertexIndex + 1] = convertY(designCoords[designIndex + 1], canvasHeight);     // Y
        vertices[vertexIndex + 2] = 0.0f;                                                      // Z

        // Konversi Warna dari 0-255 ke 0.0-1.0
        vertices[vertexIndex + 3] = convertColor(designCoords[designIndex + 2]);  // R
        vertices[vertexIndex + 4] = convertColor(designCoords[designIndex + 3]);  // G
        vertices[vertexIndex + 5] = convertColor(designCoords[designIndex + 4]);  // B
    }

    unsigned int indices[] = { 
        0, 2, 1,
        2, 3, 0,
        0, 4, 3,
        3, 5, 4,
        3, 6, 8,
        5, 7, 8,
        7, 8, 11,
        9, 10, 11,
        10, 11, 12,
        11, 12, 8,
        12, 8, 16,
        14, 15, 8,
        15, 16, 8,
        16, 18, 13,
        13, 17, 18,
        19, 18, 20,
        13, 17, 18,
        18, 19, 20,
        19, 20, 22,
        21, 22, 31,
        32, 22, 31,
        31, 23, 24,
        24, 25, 26,
        24, 27, 26,
        37, 26, 28,
        27, 29, 28,
        29, 30, 31,
        31, 22, 33,
        33, 34, 35,
        33, 36, 38,
        36, 39, 38,
        40, 39, 38,
        33, 35, 36,
        40, 41, 42,
        40, 44, 42,
        42, 43, 44,
        43, 45, 44,
        45, 46, 44,
        46, 44, 47,
    };

    // Hitung jumlah indeks
    int numIndices = sizeof(indices) / sizeof(unsigned int);

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

        // Pkaai shaddderrr
        glUseProgram(shaderProgram);
        
        float intensity = 1.0f; // Nilai intensitas ya cok disini!

        // Kirim nilai intensitas ke shader
        int intensityLocation = glGetUniformLocation(shaderProgram, "intensity");
        glUniform1f(intensityLocation, intensity);

        // Aktifkan program shader kita
        glUseProgram(shaderProgram);
        // Aktifkan VAO yang berisi semua konfigurasi
        glBindVertexArray(VAO); // Pastikan VAO terikat
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0); 

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
