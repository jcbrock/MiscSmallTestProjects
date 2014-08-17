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
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

float* CrossProduct(float vec1[], float vec2[])
{
    float cross[3];


    return cross;
}
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
    float counter = 0;

    int loopCounter = 0;

    float Ax = 0.0;
    float Ay = 0.0;
    float Bx = 0.0;
    float By = 0.0;
    std::cout << "Input Ax: " << std::endl;
    std::cin >> Ax;
    std::cout << "Input Ay: " << std::endl;
    std::cin >> Ay;
    std::cout << "Input Bx: " << std::endl;
    std::cin >> Bx;
    std::cout << "Input By: " << std::endl;
    std::cin >> By;
    
    //Calculate dot product so we can get the angle
    float dot = Ax * Bx + Ay * By;
    dot = dot / (sqrt(Ax * Ax + Ay * Ay));
    dot = dot / (sqrt(Bx * Bx + By * By));
    float foundAngle = acos(dot);

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

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
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
      
        //...        
        //glm::mat4 MVP = Projection * View * Model;


        //glUniformMatrix4fv(glGetUniformLocation(shaderprogram_spaceship, "MVP_matrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
        // glget

        // glPushMatrix();
        //glTranslatef(position.x, position.y, position.z);
        glMultMatrixf(glm::value_ptr(ModelMatrix));
        // glCallList(modelID);
        // glPopMatrix();

        // You can now use ModelMatrix to build the MVP matrix

        //then this is what i pass to glLoadMatrix???

        // glLoadMatrixf(ModelMatrix);
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
