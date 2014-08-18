#include <iostream>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#define M_PI       3.14159265358979323846
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <array>


float DistanceFromLine(float x0, float y0, float x1, float y1, float xDiff, float yDiff)
{
    //Compute A, B, C coefficents
    //A = (y0 - y1)
    //B = (x1 - x0)
    //C = (x0y1 - x1y0)
    float A = y0 - y1;
    float B = x1 - x0;
    float C = x0*y1 - x1*y0;

    float fAB = A * xDiff + B * yDiff + C;
    return fAB / (sqrt(A * A + B * B));
}

//goddamn this would be much easier with a data struct
//Alright, not going to test this for now... wait until I have a ray tracer or something?
bool IntersectedSphere(float eX, float eY, float eZ, float dX, float dY, float dZ, float cX, float cY, float cZ, float r)
{
    float eXMinuscX = eX - cX;
    float eYMinuscY = eY - cY;
    float eZMinuscZ = eZ - cZ;
    float dDotEMinusC = dX * eXMinuscX + dY * eYMinuscY + dZ * eZMinuscZ;
    float dDotd = dX * dX + dY * dY + dZ * dZ;
    float eMinusCDotted = eXMinuscX * eXMinuscX + eYMinuscY * eYMinuscY + eZMinuscZ * eZMinuscZ;
    float det = dDotEMinusC * dDotEMinusC - eMinusCDotted - r * r;

    if (det < 0)
        return false;

    float t1 = (dDotEMinusC + sqrt(det)) / dDotd;
    float t2 = (dDotEMinusC - sqrt(det)) / dDotd;

    return true;
}


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


void MultiplyMatrices4by4OpenGL_FLOAT(float *result, float *matrix1, float *matrix2)
{
    result[0] = matrix1[0] * matrix2[0] +
        matrix1[4] * matrix2[1] +
        matrix1[8] * matrix2[2] +
        matrix1[12] * matrix2[3];
    result[4] = matrix1[0] * matrix2[4] +
        matrix1[4] * matrix2[5] +
        matrix1[8] * matrix2[6] +
        matrix1[12] * matrix2[7];
    result[8] = matrix1[0] * matrix2[8] +
        matrix1[4] * matrix2[9] +
        matrix1[8] * matrix2[10] +
        matrix1[12] * matrix2[11];
    result[12] = matrix1[0] * matrix2[12] +
        matrix1[4] * matrix2[13] +
        matrix1[8] * matrix2[14] +
        matrix1[12] * matrix2[15];
    result[1] = matrix1[1] * matrix2[0] +
        matrix1[5] * matrix2[1] +
        matrix1[9] * matrix2[2] +
        matrix1[13] * matrix2[3];
    result[5] = matrix1[1] * matrix2[4] +
        matrix1[5] * matrix2[5] +
        matrix1[9] * matrix2[6] +
        matrix1[13] * matrix2[7];
    result[9] = matrix1[1] * matrix2[8] +
        matrix1[5] * matrix2[9] +
        matrix1[9] * matrix2[10] +
        matrix1[13] * matrix2[11];
    result[13] = matrix1[1] * matrix2[12] +
        matrix1[5] * matrix2[13] +
        matrix1[9] * matrix2[14] +
        matrix1[13] * matrix2[15];
    result[2] = matrix1[2] * matrix2[0] +
        matrix1[6] * matrix2[1] +
        matrix1[10] * matrix2[2] +
        matrix1[14] * matrix2[3];
    result[6] = matrix1[2] * matrix2[4] +
        matrix1[6] * matrix2[5] +
        matrix1[10] * matrix2[6] +
        matrix1[14] * matrix2[7];
    result[10] = matrix1[2] * matrix2[8] +
        matrix1[6] * matrix2[9] +
        matrix1[10] * matrix2[10] +
        matrix1[14] * matrix2[11];
    result[14] = matrix1[2] * matrix2[12] +
        matrix1[6] * matrix2[13] +
        matrix1[10] * matrix2[14] +
        matrix1[14] * matrix2[15];
    result[3] = matrix1[3] * matrix2[0] +
        matrix1[7] * matrix2[1] +
        matrix1[11] * matrix2[2] +
        matrix1[15] * matrix2[3];
    result[7] = matrix1[3] * matrix2[4] +
        matrix1[7] * matrix2[5] +
        matrix1[11] * matrix2[6] +
        matrix1[15] * matrix2[7];
    result[11] = matrix1[3] * matrix2[8] +
        matrix1[7] * matrix2[9] +
        matrix1[11] * matrix2[10] +
        matrix1[15] * matrix2[11];
    result[15] = matrix1[3] * matrix2[12] +
        matrix1[7] * matrix2[13] +
        matrix1[11] * matrix2[14] +
        matrix1[15] * matrix2[15];
}

void MultiplyMatrixByVector4by4OpenGL_FLOAT(float *resultvector, const float *matrix, const float *pvector)
{
    resultvector[0] = matrix[0] * pvector[0] + matrix[4] * pvector[1] + matrix[8] * pvector[2] + matrix[12] * pvector[3];
    resultvector[1] = matrix[1] * pvector[0] + matrix[5] * pvector[1] + matrix[9] * pvector[2] + matrix[13] * pvector[3];
    resultvector[2] = matrix[2] * pvector[0] + matrix[6] * pvector[1] + matrix[10] * pvector[2] + matrix[14] * pvector[3];
    resultvector[3] = matrix[3] * pvector[0] + matrix[7] * pvector[1] + matrix[11] * pvector[2] + matrix[15] * pvector[3];
}

#define SWAP_ROWS_DOUBLE(a, b) { double *_tmp = a; (a) = (b); (b) = _tmp; }
#define SWAP_ROWS_FLOAT(a, b) { float *_tmp = a; (a) = (b); (b) = _tmp; }
#define MAT(m, r, c) (m)[(c)* 4 + (r)]

//This code comes directly from GLU except that it is for float
int glhInvertMatrixf2(float *m, float *out)
{
    float wtmp[4][8];
    float m0, m1, m2, m3, s;
    float *r0, *r1, *r2, *r3;
    r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];
    r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1),
        r0[2] = MAT(m, 0, 2), r0[3] = MAT(m, 0, 3),
        r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
        r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1),
        r1[2] = MAT(m, 1, 2), r1[3] = MAT(m, 1, 3),
        r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
        r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1),
        r2[2] = MAT(m, 2, 2), r2[3] = MAT(m, 2, 3),
        r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
        r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1),
        r3[2] = MAT(m, 3, 2), r3[3] = MAT(m, 3, 3),
        r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
    /* choose pivot - or die */
    if (fabsf(r3[0]) > fabsf(r2[0]))
        SWAP_ROWS_FLOAT(r3, r2);
    if (fabsf(r2[0]) > fabsf(r1[0]))
        SWAP_ROWS_FLOAT(r2, r1);
    if (fabsf(r1[0]) > fabsf(r0[0]))
        SWAP_ROWS_FLOAT(r1, r0);
    if (0.0 == r0[0])
        return 0;
    /* eliminate first variable     */
    m1 = r1[0] / r0[0];
    m2 = r2[0] / r0[0];
    m3 = r3[0] / r0[0];
    s = r0[1];
    r1[1] -= m1 * s;
    r2[1] -= m2 * s;
    r3[1] -= m3 * s;
    s = r0[2];
    r1[2] -= m1 * s;
    r2[2] -= m2 * s;
    r3[2] -= m3 * s;
    s = r0[3];
    r1[3] -= m1 * s;
    r2[3] -= m2 * s;
    r3[3] -= m3 * s;
    s = r0[4];
    if (s != 0.0) {
        r1[4] -= m1 * s;
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r0[5];
    if (s != 0.0) {
        r1[5] -= m1 * s;
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r0[6];
    if (s != 0.0) {
        r1[6] -= m1 * s;
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r0[7];
    if (s != 0.0) {
        r1[7] -= m1 * s;
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }
    /* choose pivot - or die */
    if (fabsf(r3[1]) > fabsf(r2[1]))
        SWAP_ROWS_FLOAT(r3, r2);
    if (fabsf(r2[1]) > fabsf(r1[1]))
        SWAP_ROWS_FLOAT(r2, r1);
    if (0.0 == r1[1])
        return 0;
    /* eliminate second variable */
    m2 = r2[1] / r1[1];
    m3 = r3[1] / r1[1];
    r2[2] -= m2 * r1[2];
    r3[2] -= m3 * r1[2];
    r2[3] -= m2 * r1[3];
    r3[3] -= m3 * r1[3];
    s = r1[4];
    if (0.0 != s) {
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r1[5];
    if (0.0 != s) {
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r1[6];
    if (0.0 != s) {
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r1[7];
    if (0.0 != s) {
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }
    /* choose pivot - or die */
    if (fabsf(r3[2]) > fabsf(r2[2]))
        SWAP_ROWS_FLOAT(r3, r2);
    if (0.0 == r2[2])
        return 0;
    /* eliminate third variable */
    m3 = r3[2] / r2[2];
    r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
        r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];
    /* last check */
    if (0.0 == r3[3])
        return 0;
    s = 1.0 / r3[3];		/* now back substitute row 3 */
    r3[4] *= s;
    r3[5] *= s;
    r3[6] *= s;
    r3[7] *= s;
    m2 = r2[3];			/* now back substitute row 2 */
    s = 1.0 / r2[2];
    r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
        r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
    m1 = r1[3];
    r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
        r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
    m0 = r0[3];
    r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
        r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
    m1 = r1[2];			/* now back substitute row 1 */
    s = 1.0 / r1[1];
    r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
        r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
    m0 = r0[2];
    r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
        r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
    m0 = r0[1];			/* now back substitute row 0 */
    s = 1.0 / r0[0];
    r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
        r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
    MAT(out, 0, 0) = r0[4];
    MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6];
    MAT(out, 0, 3) = r0[7], MAT(out, 1, 0) = r1[4];
    MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6];
    MAT(out, 1, 3) = r1[7], MAT(out, 2, 0) = r2[4];
    MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6];
    MAT(out, 2, 3) = r2[7], MAT(out, 3, 0) = r3[4];
    MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6];
    MAT(out, 3, 3) = r3[7];
    return 1;
}

int glhProjectf(float objx, float objy, float objz, float *modelview, float *projection, int *viewport, float *windowCoordinate)
{
    //Transformation vectors
    float fTempo[8];
    //Modelview transform
    fTempo[0] = modelview[0] * objx + modelview[4] * objy + modelview[8] * objz + modelview[12];  //w is always 1
    fTempo[1] = modelview[1] * objx + modelview[5] * objy + modelview[9] * objz + modelview[13];
    fTempo[2] = modelview[2] * objx + modelview[6] * objy + modelview[10] * objz + modelview[14];
    fTempo[3] = modelview[3] * objx + modelview[7] * objy + modelview[11] * objz + modelview[15];
    //Projection transform, the final row of projection matrix is always [0 0 -1 0]
    //so we optimize for that.
    fTempo[4] = projection[0] * fTempo[0] + projection[4] * fTempo[1] + projection[8] * fTempo[2] + projection[12] * fTempo[3];
    fTempo[5] = projection[1] * fTempo[0] + projection[5] * fTempo[1] + projection[9] * fTempo[2] + projection[13] * fTempo[3];
    fTempo[6] = projection[2] * fTempo[0] + projection[6] * fTempo[1] + projection[10] * fTempo[2] + projection[14] * fTempo[3];
    fTempo[7] = -fTempo[2];
    //The result normalizes between -1 and 1
    if (fTempo[7] == 0.0)	//The w value
        return 0;
    fTempo[7] = 1.0 / fTempo[7];
    //Perspective division
    fTempo[4] *= fTempo[7];
    fTempo[5] *= fTempo[7];
    fTempo[6] *= fTempo[7];
    //Window coordinates
    //Map x, y to range 0-1
    windowCoordinate[0] = (fTempo[4] * 0.5 + 0.5)*viewport[2] + viewport[0];
    windowCoordinate[1] = (fTempo[5] * 0.5 + 0.5)*viewport[3] + viewport[1];
    //This is only correct when glDepthRange(0.0, 1.0)
    windowCoordinate[2] = (1.0 + fTempo[6])*0.5;	//Between 0 and 1
    return 1;
}

int glhUnProjectf(float winx, float winy, float winz, float *modelview, float *projection, int *viewport, float *objectCoordinate)
{
    //Transformation matrices
    float m[16], A[16];
    float in[4], out[4];
    //Calculation for inverting a matrix, compute projection x modelview
    //and store in A[16]
    MultiplyMatrices4by4OpenGL_FLOAT(A, projection, modelview);
    //Now compute the inverse of matrix A
    if (glhInvertMatrixf2(A, m) == 0)
        return 0;
    //Transformation of normalized coordinates between -1 and 1
    in[0] = (winx - (float)viewport[0]) / (float)viewport[2] * 2.0 - 1.0;
    in[1] = (winy - (float)viewport[1]) / (float)viewport[3] * 2.0 - 1.0;
    in[2] = 2.0*winz - 1.0;
    in[3] = 1.0;
    //Objects coordinates
    MultiplyMatrixByVector4by4OpenGL_FLOAT(out, m, in);
    if (out[3] == 0.0)
        return 0;
    out[3] = 1.0 / out[3];
    objectCoordinate[0] = out[0] * out[3];
    objectCoordinate[1] = out[1] * out[3];
    objectCoordinate[2] = out[2] * out[3];
    return 1;
}

void windowToObjectf(const glm::vec3& windowCoord, float * ret) {
    glm::mat4 modelViewMatrix;
    glm::mat4 projectionMatrix;
    std::array <GLint, 4> viewport;
    glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelViewMatrix));
    glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(projectionMatrix));
    glGetIntegerv(GL_VIEWPORT, &viewport.front());
    //glm::vec3 ret(0, 0, 0);
    //float* ret = new float[3];

    int success = glhUnProjectf(windowCoord.x, windowCoord.y, windowCoord.z, glm::value_ptr(modelViewMatrix), glm::value_ptr(projectionMatrix), &viewport.front(), ret);
    //RASSERT(succes == GL_TRUE);
    //GL_RASSERT();
    std::cout << "success: " << success << std::endl;

    //return ret;
}


void onMouseButton(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {

        double* xpos = new double();
        double* ypos = new double();

        glfwGetCursorPos(window, xpos, ypos);
        // ... some code
        std::cout << "Right click! (" << *xpos << ", " << *ypos << ")" << std::endl;

        // glm::vec3 windowPos(1.0, 1.0, 0);
        float xf = (float)(*xpos);
        float yf = (float)(*ypos);
        //float yf = (float)std::numeric_limits<double>::infinity();
        glm::vec3 windowPos(xf, yf, 0);
        float * coords = new float[3];
        windowToObjectf(windowPos, coords);
        //Ok, how am I going to define my scene? i.e. how do I make opengl match what my internal data is?
        std::cout << "windowToObjectf returned: (" << coords[0] << ", " << coords[1] << ", " << coords[2] << ")" << std::endl;
        delete coords;

        //ok, so I now have a way to test collision with an object between my mouse click and opengl
        //ok, I can now tell where I clicked on the screen, and where I clicked in object space. I can
        //confirm collision with openGL in object space. How do I detect collision with my scene?
        //This might be where I read about transforms and camera stuff...



        delete xpos;
        delete ypos;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        double* xpos = new double();
        double* ypos = new double();

        glfwGetCursorPos(window, xpos, ypos);
        // ... some code
        std::cout << "Left click! (" << *xpos << ", " << *ypos << ")" << std::endl;

        delete xpos;
        delete ypos;
    }
}

float* CrossProduct(float vec1[], float vec2[])
{
    float cross[3];


    return cross;
}

//InitOpenGL
//Setup camera
//InitLoopStuff
//DoSceneStuff
//EndLoopStuff
//EndOpenGLStuff


int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        system("pause");
        exit(EXIT_FAILURE);
        system("pause");
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, onMouseButton);

    std::cout << "(0,0) -> (2,2), test (2,1): " << DistanceFromLine(0, 0, 2, 2, 1, 2) << std::endl; // should be 1/sqrt(2) / .707...
    std::cout << "(0,0) -> (2,2), test (0, 2): " << DistanceFromLine(0, 0, 2, 2, 0, 2) << std::endl; //should be sqrt(2) 1.414...



    float counter = 0;

    int loopCounter = 0;

    float Ax = 0.0;
    float Ay = 0.0;
    float Bx = 0.0;
    float By = 0.0;
    std::cout << "Input Ax: " << std::endl;
    //std::cin >> Ax;
    std::cout << "Input Ay: " << std::endl;
    //std::cin >> Ay;
    std::cout << "Input Bx: " << std::endl;
    //std::cin >> Bx;
    std::cout << "Input By: " << std::endl;
    //std::cin >> By;

    //Calculate dot product so we can get the angle
    /*float dot = Ax * Bx + Ay * By;
    dot = dot / (sqrt(Ax * Ax + Ay * Ay));
    dot = dot / (sqrt(Bx * Bx + By * By));
    float foundAngle = acos(dot);
    */
    //Calculate cross product vector





    glm::mat4 ModelMatrix;

    glm::detail::tquat<float, glm::precision::highp> MyQuaternion;
    glm::detail::tvec3<float, glm::precision::highp> RotationAxis(0, 1, 0);

    float RotationAngle = 45;
    RotationAngle = (M_PI / 180) * RotationAngle;;
    MyQuaternion = glm::angleAxis(glm::degrees(RotationAngle), RotationAxis);
    glm::mat4 foobar(1.0f);

    glm::mat4 RotationMatrix = glm::toMat4<float, glm::precision::highp>(MyQuaternion);
    //...
    ModelMatrix = RotationMatrix;

    //How does a ray tracer work?
    //I need an empty buffer that I'll loop over, send out a ray to the scene
    //I'll see if it hits anything (I'll start out with a list of shapes)
    //And then that will color the pixel, I stick it in hte buffer, and then we're good.






    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        if (loopCounter % 25000 == 0)
        {

            std::cout << "FrameBuffer height: " << height << std::endl;
            std::cout << "FrameBuffer width: " << width << std::endl;
        }

        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /*
        glm::mat4 ModelMatrix;
        if (loopCounter == 0)
        {
        glm::detail::tquat<float, glm::precision::highp> MyQuaternion;
        glm::detail::tvec3<float, glm::precision::highp> RotationAxis(0, 1, 0);
        float RotationAngle = 45;
        MyQuaternion = glm::angleAxis(glm::degrees(RotationAngle), RotationAxis);
        glm::mat4 foobar(1.0f);

        glm::mat4 RotationMatrix = glm::toMat4<float, glm::precision::highp>(MyQuaternion);
        //...
        ModelMatrix = RotationMatrix;
        }
        else
        {
        // RotationAngle is in radians
        // x = RotationAxis.x * sin(RotationAngle / 2);
        // y = RotationAxis.y * sin(RotationAngle / 2);
        //  z = RotationAxis.z * sin(RotationAngle / 2);
        //  w = cos(RotationAngle / 2);

        // Creates an identity quaternion (no rotation)
        glm::detail::tquat<float, glm::precision::highp> MyQuaternion;

        // Direct specification of the 4 components
        // You almost never use this directly
        // MyQuaternion = glm::quat(w, x, y, z);

        // Conversion from Euler angles (in radians) to Quaternion
        // glm::vec3 EulerAngles(90, 45, 0);
        // MyQuaternion = glm::quat(EulerAngles);

        // Conversion from axis-angle
        // In GLM the angle must be in degrees here, so convert it.
        glm::detail::tvec3<float, glm::precision::highp> RotationAxis(0, 1, 0);

        counter += 1;
        //counter += M_PI;
        if (counter > 90.0)
        {
        counter = 0;
        }

        //convert to radians
        float RotationAngle = (M_PI / 180) * counter;;

        MyQuaternion = glm::angleAxis(glm::degrees(RotationAngle), RotationAxis);
        //convert the quat into a axis-angle rotation matrix, which is the same kind of matrix
        //that glRotate constructs and multiplies onto the matrix stack. In our case,
        //we can just store it to the OpenGL matrix stack using glLoadMatrix.
        glm::mat4 foobar(1.0f);

        glm::mat4 RotationMatrix = glm::toMat4<float, glm::precision::highp>(MyQuaternion);
        ModelMatrix = RotationMatrix;
        }
        */


        //glMultMatrixf(glm::value_ptr(ModelMatrix));

        //glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();



        glfwSwapBuffers(window);
        glfwPollEvents();

        //if (loopCounter == 0)
        //{
        //system("pause");
        //}

        if (loopCounter == INT_MAX)
        {
            loopCounter = 0;
        }
        else
            ++loopCounter;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    system("pause");
}
