#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 vPosition;\n"
"layout (location = 1) in vec3 vColor;\n"
"out vec3 fragColor;\n"
"void main() {\n"
"   gl_Position = vec4(vPosition, 0.0, 1.0);\n"
"   fragColor = vColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 fragColor;\n"
"out vec4 finalColor;\n"
"void main() {\n"
"   finalColor = vec4(fragColor, 1.0);\n"
"}\0";

GLuint VAO, VBO, shaderProgram;
std::vector<float> vertices;

void addVertex(float x, float y, float r, float g, float b) {
    vertices.push_back(x); vertices.push_back(y);
    vertices.push_back(r); vertices.push_back(g); vertices.push_back(b);
}

void buildShapes() {
    const float PI = 3.14159265f;

    // 1. Concentric Squares (Center)[cite: 24]
    float sizes[] = { 0.6f, 0.45f, 0.3f, 0.15f, 0.05f };
    for (int i = 0; i < 5; ++i) {
        float c = (i % 2 == 0) ? 1.0f : 0.0f; // Alternate white and black[cite: 24]
        // Start at pi/4, increment by pi/2[cite: 24]
        for (int j = 0; j < 4; ++j) {
            float angle = (PI / 4.0f) + (j * PI / 2.0f);
            addVertex(sizes[i] * cos(angle), sizes[i] * sin(angle) - 0.2f, c, c, c);
        }
    }

    // 2. Red Ellipse (Top Left)[cite: 23, 24]
    addVertex(-0.6f, 0.7f, 1.0f, 0.0f, 0.0f); // Center
    for (int i = 0; i <= 36; ++i) {
        float angle = i * 2.0f * PI / 36.0f;
        // Scale y down to 60%[cite: 24]
        addVertex(-0.6f + 0.2f * cos(angle), 0.7f + 0.2f * 0.6f * sin(angle), 1.0f, 0.0f, 0.0f);
    }

    // 3. RGB Triangle (Top Center)[cite: 24]
    addVertex(0.0f, 0.9f, 1.0f, 0.0f, 0.0f);  // Top Red
    addVertex(-0.2f, 0.5f, 0.0f, 1.0f, 0.0f); // Bottom Left Green
    addVertex(0.2f, 0.5f, 0.0f, 0.0f, 1.0f);  // Bottom Right Blue

    // 4. Shaded Circle (Top Right)[cite: 23, 24]
    addVertex(0.6f, 0.7f, 0.1f, 0.0f, 0.0f); // Center dark red[cite: 23]
    for (int i = 0; i <= 36; ++i) {
        float angle = i * 2.0f * PI / 36.0f;
        // Vary red color as a function of angle[cite: 24]
        float redIntensity = 0.3f + 0.7f * (0.5f * (1.0f + cos(angle)));
        addVertex(0.6f + 0.2f * cos(angle), 0.7f + 0.2f * sin(angle), redIntensity, 0.0f, 0.0f);
    }
}

void init() {
    buildShapes();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // vPosition[cite: 23]
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // vColor[cite: 23]
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    int offset = 0;
    // Draw 5 Squares (GL_TRIANGLE_FAN)[cite: 23, 24]
    for (int i = 0; i < 5; ++i) {
        glDrawArrays(GL_TRIANGLE_FAN, offset, 4);
        offset += 4;
    }
    // Draw Ellipse (GL_TRIANGLE_FAN)[cite: 23, 24]
    glDrawArrays(GL_TRIANGLE_FAN, offset, 38); offset += 38;
    // Draw Triangle (GL_TRIANGLES)[cite: 23, 24]
    glDrawArrays(GL_TRIANGLES, offset, 3); offset += 3;
    // Draw Shaded Circle (GL_TRIANGLE_FAN)[cite: 23, 24]
    glDrawArrays(GL_TRIANGLE_FAN, offset, 38);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // 500x500 window requirement[cite: 24]
    glutCreateWindow("Assignment 1 - Task 2");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
