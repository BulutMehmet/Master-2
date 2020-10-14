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

    GLuint vbo, vao;
    int nbTriangles;
    cout << "entrez le nombre de triangles" << endl;
    cin >> nbTriangles;
    float rayon = 0.5f;
    glm::vec2 origin(0.f, 0.f);
    float angle = (2 * glm::pi<float>()) / nbTriangles;
    Vertex2DColor vertices[nbTriangles * 3];
    
    for( int i = 0; i < nbTriangles; i++) {
        cout << "angle = " << angle*i << " " << 2 * glm::pi<float>() << endl;
        float pointAX = rayon * glm::cos(angle * i);
        float pointAY = rayon * glm::sin(angle * i);
        float pointBX = rayon * glm::cos(angle * (i+1) );
        float pointBY = rayon * glm::sin(angle * (i+1) );

        vertices[i*3] = Vertex2DColor(origin, glm::vec3(1.f, 0.f, 0.f));
        vertices[i*3 + 1] = Vertex2DColor(glm::vec2(pointAX, pointAY), glm::vec3(0.f, 1.f, 0.f));
        vertices[i*3 + 2] = Vertex2DColor(glm::vec2(pointBX, pointBY), glm::vec3(0.f, 1.f, 0.f));
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, nbTriangles * 3 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
    glBindBuffer(0, vbo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
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
        glDrawArrays(GL_TRIANGLES, 0, nbTriangles * 3);
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
