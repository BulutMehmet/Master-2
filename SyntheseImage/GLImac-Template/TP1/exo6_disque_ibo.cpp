#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

using namespace glimac;
using namespace std;
const int VERTEX_ATTR_POSITION = 3;
const int VERTEX_ATTR_COLOR = 8;

struct Vertex2DColor {
    glm::vec2 position;
    glm::vec3 color;

    Vertex2DColor() {
        position = glm::vec2(0.f, 0.f);
        color = glm::vec3(0.f, 0.f, 0.f);
    }

    Vertex2DColor(glm::vec2 pos, glm::vec3 col){
        position = pos;
        color = col;
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    FilePath applicationPath(argv[0]);
    Program program = loadProgram(  applicationPath.dirPath() + "shaders/triangle.vs.glsl",
                                    applicationPath.dirPath() + "shaders/triangle.fs.glsl");
    program.use();
    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    GLuint vbo, vao, ibo;
    int nbTriangles;
    cout << "entrez le nombre de triangles" << endl;
    cin >> nbTriangles;
    cout << "ok" << endl;
    float rayon = 0.5f;
    glm::vec2 origin(0.f, 0.f);
    float angle = (2 * glm::pi<float>()) / nbTriangles;
    cout << "ok" << endl;

    Vertex2DColor vertices[nbTriangles + 1];
        cout << "ok" << endl;
    int indexes[nbTriangles * 3];
        cout << "ok" << endl;

    vertices[0] = Vertex2DColor(origin, glm::vec3(1.f, 0.f, 0.f));
    for( int i = 0; i < nbTriangles; i++) {
        cout << i << endl;
        float pointAX = rayon * glm::cos(angle * i);
        float pointAY = rayon * glm::sin(angle * i);

        vertices[i+1] = Vertex2DColor(glm::vec2(pointAX, pointAY), glm::vec3(1.f, 0.f, 0.f));
        indexes[i * 3] = 0;
        indexes[i*3 + 1] = i+1;

        if(i >= nbTriangles - 1)
            indexes[i*3 + 2] = 1;
        else
            indexes[i*3 + 2] = i+2;
    }

    cout << endl;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (nbTriangles + 1) * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
    glBindBuffer(0, vbo);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbTriangles * 3 * sizeof(int), indexes, GL_STATIC_DRAW);
    glBindBuffer(0, ibo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, position));
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, color));
    glBindBuffer(0, vbo);
    glBindVertexArray(0);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, nbTriangles * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
