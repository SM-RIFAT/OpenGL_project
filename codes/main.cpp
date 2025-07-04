#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>


float eyeX = 0.0f, eyeY = 2.0f, eyeZ = 8.0f;

float focusX = 0.0f, focusY = 0.0f, focusZ = 0.0f;

float cubeX = -2.5f, cubeY = 0.0f, cubeZ = 0.0f;
float sphereX = 0.0f, sphereY = 0.0f, sphereZ = 0.0f;
float pyramidX = 2.5f, pyramidY = 0.0f, pyramidZ = 0.0f;


float cubeRotX = 0.0f, cubeRotY = 0.0f;
float sphereRotX = 0.0f, sphereRotY = 0.0f;
float pyramidRotX = 0.0f, pyramidRotY = 0.0f;


float cubeScale = 1.0f;
float sphereScale = 1.0f;
float pyramidScale = 1.0f;


float lightPos[] = {0.0f, 5.0f, 0.0f, 1.0f};


GLuint cubeTexture;
GLuint groundTexture;


void generateCubeTexture() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &cubeTexture);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);

    const int width = 32, height = 32;
    unsigned char textureData[width][height][3];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if ((i / 4 + j / 4) % 2 == 0) {
                textureData[i][j][0] = 0;
                textureData[i][j][1] = 0;
                textureData[i][j][2] = 0;
            } else {
                textureData[i][j][0] = 255;
                textureData[i][j][1] = 255;
                textureData[i][j][2] = 255;
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void generateGroundTexture() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &groundTexture);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

    const int width = 64, height = 64;
    unsigned char textureData[width][height][3];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if ((i / 8 + j / 8) % 2 == 0) {
                textureData[i][j][0] = 180;
                textureData[i][j][1] = 180;
                textureData[i][j][2] = 180;
            } else {
                textureData[i][j][0] = 220;
                textureData[i][j][1] = 220;
                textureData[i][j][2] = 220;
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}


void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}


void drawCube() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glColor3f(1.0f, 0.0f, 0.0f); // Red tint

    glBegin(GL_QUADS);
    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void drawSphere() {
    const int slices = 20, stacks = 20;
    const float radius = 1.0f;
    glBegin(GL_QUADS);
    for (int i = 0; i < stacks; i++) {
        float lat0 = M_PI * (-0.5f + (float)i / stacks);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);
        float lat1 = M_PI * (-0.5f + (float)(i + 1) / stacks);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        for (int j = 0; j < slices; j++) {
            float lng0 = 2 * M_PI * (float)j / slices;
            float x0 = cos(lng0);
            float y0 = sin(lng0);
            float lng1 = 2 * M_PI * (float)(j + 1) / slices;
            float x1 = cos(lng1);
            float y1 = sin(lng1);

            float t = (float)(i + 0.5f) / stacks;
            float r = 0.0f;
            float g = 0.2f + t * 0.3f;
            float b = 0.5f + t * 0.5f;

            glNormal3f(x0 * zr0, y0 * zr0, z0);
            glColor3f(r, g, b);
            glVertex3f(radius * x0 * zr0, radius * y0 * zr0, radius * z0);

            glNormal3f(x1 * zr0, y1 * zr0, z0);
            glColor3f(r, g, b);
            glVertex3f(radius * x1 * zr0, radius * y1 * zr0, radius * z0);

            glNormal3f(x1 * zr1, y1 * zr1, z1);
            glColor3f(r, g + 0.3f * (z1 + 1) / 2, b + 0.5f * (z1 + 1) / 2);
            glVertex3f(radius * x1 * zr1, radius * y1 * zr1, radius * z1);

            glNormal3f(x0 * zr1, y0 * zr1, z1);
            glColor3f(r, g + 0.3f * (z1 + 1) / 2, b + 0.5f * (z1 + 1) / 2);
            glVertex3f(radius * x0 * zr1, radius * y0 * zr1, radius * z1);
        }
    }
    glEnd();
}


void drawPyramid() {
    glBegin(GL_TRIANGLES);
    // Front face
    glNormal3f(0.0f, 0.4472f, 0.8944f);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    // Right face
    glNormal3f(0.8944f, 0.4472f, 0.0f);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    // Back face
    glNormal3f(0.0f, 0.4472f, -0.8944f);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    // Left face
    glNormal3f(-0.8944f, 0.4472f, 0.0f);
    glColor3f(1.0f, 0.6f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();
}


void drawGround() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -1.0f, -10.0f);
    glTexCoord2f(10.0f, 0.0f); glVertex3f(10.0f, -1.0f, -10.0f);
    glTexCoord2f(10.0f, 10.0f); glVertex3f(10.0f, -1.0f, 10.0f);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-10.0f, -1.0f, 10.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void drawSky() {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.8f);
    glVertex3f(-20.0f, 10.0f, -20.0f);
    glVertex3f(20.0f, 10.0f, -20.0f);
    glVertex3f(20.0f, 10.0f, 20.0f);
    glVertex3f(-20.0f, 10.0f, 20.0f);
    glEnd();
    glEnable(GL_LIGHTING);
}


void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(eyeX, eyeY, eyeZ, focusX, focusY, focusZ, 0.0f, 1.0f, 0.0f);

    drawSky();
    drawGround();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glPushMatrix();
    glTranslatef(cubeX, cubeY, cubeZ);
    glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
    glScalef(cubeScale, cubeScale, cubeScale);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sphereX, sphereY, sphereZ);
    glRotatef(sphereRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(sphereRotY, 0.0f, 1.0f, 0.0f);
    glScalef(sphereScale, sphereScale, sphereScale);
    drawSphere();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pyramidX, pyramidY, pyramidZ);
    glRotatef(pyramidRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(pyramidRotY, 0.0f, 1.0f, 0.0f);
    glScalef(pyramidScale, pyramidScale, pyramidScale);
    drawPyramid();
    glPopMatrix();

    glutSwapBuffers();
}

// Update function for animations
void update(int value) {
    // Animate cube: rotate around both X and Y axes
    cubeRotX += 1.0f;
    cubeRotY += 1.5f;
    if (cubeRotX >= 360.0f) cubeRotX -= 360.0f;
    if (cubeRotY >= 360.0f) cubeRotY -= 360.0f;

    // Animate sphere: rotate around Y axis
    sphereRotY += 2.0f;
    if (sphereRotY >= 360.0f) sphereRotY -= 360.0f;

    // Animate pyramid: rotate around X axis
    pyramidRotX += 1.2f;
    if (pyramidRotX >= 360.0f) pyramidRotX -= 360.0f;

    glutPostRedisplay(); // Request redraw
    glutTimerFunc(16, update, 0); // ~60 FPS
}

// Keyboard input handling
void handleKeyboard(unsigned char key, int x, int y) {
    float moveStep = 0.2f;  // Translation step for objects and camera
    float rotStep = 5.0f;   // Rotation step
    float scaleStep = 0.1f; // Scaling step

    switch (key) {
        // Cube controls
        case 'q': cubeX -= moveStep; break; // Move left
        case 'e': cubeX += moveStep; break; // Move right
        case 'w': cubeY += moveStep; break; // Move up
        case 's': cubeY -= moveStep; break; // Move down
        case 'a': cubeZ -= moveStep; break; // Move forward
        case 'd': cubeZ += moveStep; break; // Move backward
        case 'r': cubeRotX += rotStep; break; // Rotate X
        case 't': cubeRotY += rotStep; break; // Rotate Y
        case 'f': cubeScale += scaleStep; break; // Scale up
        case 'g': if (cubeScale > 0.1f) cubeScale -= scaleStep; break; // Scale down

        // Sphere controls
        case 'u': sphereX -= moveStep; break; // Move left
        case 'o': sphereX += moveStep; break; // Move right
        case 'i': sphereY += moveStep; break; // Move up
        case 'k': sphereY -= moveStep; break; // Move down
        case 'j': sphereZ -= moveStep; break; // Move forward
        case 'l': sphereZ += moveStep; break; // Move backward
        case 'p': sphereRotX += rotStep; break; // Rotate X
        case '[': sphereRotY += rotStep; break; // Rotate Y
        case 'h': sphereScale += scaleStep; break; // Scale up
        case 'n': if (sphereScale > 0.1f) sphereScale -= scaleStep; break; // Scale down

        // Pyramid controls
        case '1': pyramidX -= moveStep; break; // Move left
        case '3': pyramidX += moveStep; break; // Move right
        case '2': pyramidY += moveStep; break; // Move up
        case '5': pyramidY -= moveStep; break; // Move down
        case '4': pyramidZ -= moveStep; break; // Move forward
        case '6': pyramidZ += moveStep; break; // Move backward
        case '7': pyramidRotX += rotStep; break; // Rotate X
        case '8': pyramidRotY += rotStep; break; // Rotate Y
        case '9': pyramidScale += scaleStep; break; // Scale up
        case '0': if (pyramidScale > 0.1f) pyramidScale -= scaleStep; break; // Scale down

        // Camera controls
        case 'z': eyeX -= moveStep; break; // Move camera left
        case 'x': eyeX += moveStep; break; // Move camera right
        case 'c': eyeY += moveStep; break; // Move camera up
        case 'v': eyeY -= moveStep; break; // Move camera down
        case 'b': eyeZ -= moveStep; break; // Move camera forward
        case 'y': eyeZ += moveStep; break; // Move camera backward
        case ';': focusX -= moveStep; break; // Pan focus left
        case '\'': focusX += moveStep; break; // Pan focus right
        case ']': focusY += moveStep; break; // Pan focus up
        case '\\': focusY -= moveStep; break; // Pan focus down

        case 27: exit(0); break; // ESC to exit
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, 4.0 / 3.0, 0.1f, 50.0f);
    glMatrixMode(GL_MODELVIEW);

    setupLighting();
    generateCubeTexture();
    generateGroundTexture();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Objects with Animations and Environment");
    init();
    glutDisplayFunc(render);
    glutKeyboardFunc(handleKeyboard);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
