//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinder.h"
#include "sphere.h"
//#include "directionalLight.h"
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void building(unsigned int& cubeVAO, Shader& lightingShader, Cube& cube_brickWall, Cube& cube_woodPlatform, Shader& lightingShaderwithTex, glm::mat4 alTogether, float r1, float g1, float b1, float r2, float g2, float b2);
void centerWindow(unsigned int& cubeVAO, Shader& lightingShader, Cube& cube_woodPlatform, Shader& lightingShaderwithTex, glm::mat4 alTogether, glm::mat4 model, float r, float g, float b, float floorX, float floorY, float floorZ, float windowHeight, float wall);
void door(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, glm::mat4 model, float r, float g, float b, float floorX, float floorY, float floorZ, float wall);
void lampPost(Shader& ourShader, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void lampStand(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z);
void floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void securityLight(Shader& ourShader, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void drawtri(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b, int n);
void welcomeSign(Shader& ourShader, unsigned int& signVAO, unsigned int& signVAO1, unsigned int& signVAO2, unsigned int& signVAO3, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void roads(unsigned int& cubeVAO, Shader& lightingShader, Cube& cube_road, Shader& lightingShaderwithTex, Cube& cube_road1);
void block(glm::mat4 model, Shader& lightingShader, Cube& cube);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void restaurant(Cube& cube_cafe_sign, Cube& cube_dark_brick, Cube& cube_stone, Cube& cube_oak,Cube& cube_innerWall, Cube& cube_grey_brick, Shader& lightingShaderwithTex, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x1, float z1);
void school(Cylinder& white_cylinder, Cube& cube_window, Cube& cube_grey_brick, Shader& lightingShaderwithTex, unsigned int& cubeVAO, Shader& lightingShader, float x1, float z1);
void swing(unsigned int& cubeVAO, Shader& lightingShader, Cylinder& cylinder, glm::mat4 model, glm::mat4 ms1);
void swingRotateI();
void swingRotateB();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int swingF = 0;
int swingB = 0;
// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float pi = 1;
// camera
Camera camera(glm::vec3(2.0f, 1.1f, 5.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);
vector<float> circVer, circVer1, circR1, circR2, circR1t, h_cube;
// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;
int farest = 0, backest = 0;
void swingRotateB()
{
    if (rotateAngle_X > 0) {
        farest = 1;
        rotateAngle_X -= 25.0 * deltaTime;

        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;

        translate_Y -= 0.2 * deltaTime;
        translate_Z += 0.53 * deltaTime;
    }
    else if (rotateAngle_X >= -25 && rotateAngle_X <0) {
        farest = 1;
        rotateAngle_X -= 25.0 * deltaTime;

        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;

        translate_Y += 0.2 * deltaTime;
        translate_Z += 0.53 * deltaTime;
    }
    else {
        farest = 0;
        
    }
    
}
void swingRotateI()
{
    
    

    if (rotateAngle_X < 0) {
        farest = 0;
        rotateAngle_X += 25.0 * deltaTime;

        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;

        translate_Y -= 0.2 * deltaTime;
        translate_Z -= 0.53 * deltaTime;
    }
    else{
        farest = 0;
        rotateAngle_X += 25.0 * deltaTime;

        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;

        translate_Y += 0.2 * deltaTime;
        translate_Z -= 0.53 * deltaTime;
    }

}
void swingRotateF()
{
    rotateAngle_X += 50.0 * deltaTime;

    rotateAxis_X = 1.0;
    rotateAxis_Y = 0.0;
    rotateAxis_Z = 0.0;
    if (backest) {
        rotateAngle_X += 50.0 * deltaTime;

        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;

        farest = 1;
        backest = 0;
    }
    
}

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    //glm::vec3(-0.7f, 2.0f, 2.0f),
    glm::vec3(0.5, -3.0, -5),
    glm::vec3(1.45, 1.9, -1.55),
    glm::vec3(-0.07, 1.3f, 1.0f),
    glm::vec3(1.5f,  -1.5f,  0)
};

glm::vec3 direction[] = {
    //glm::vec3(-0.7f, 2.0f, 2.0f),
    glm::vec3(1.0, 5.0, -3),
    glm::vec3(0.0, 0.0, 0.0),
    glm::vec3(0.0, -3.0, 0)
};
PointLight pointlight1(
    //directional light

    direction[0].x, direction[0].y, direction[0].z,  // position
    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    .5, .5, .5,     // ambient
    .7, 0.7, 0.7,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
/*DirectionalLight directionalLight(
    direction[0].x, direction[0].y, direction[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.05f, 0.05f, 0.05f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);*/
PointLight pointlight2(
    //pointlight
    direction[1].x, direction[1].y, direction[1].z,
    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.1f, 0.1, 0.1,     // ambient
    0.5, 0.5, 0.5,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);

PointLight pointlight3(
    direction[2].x, direction[2].y, direction[2].z,

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.1f, 0.1, 0.1,     // ambient
    0.5, 0.5, 0.5,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(
    direction[3].x, direction[3].y, direction[3].z,

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.05f, 0.05f, 0.05f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);


// light settings
bool onOffToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;




int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    //GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor(); // The primary monitor.. Later Occulus?..

    const GLFWvidmode* mode = glfwGetVideoMode(MyMonitor);
    const unsigned int SCR_WIDTH1 = mode->width;
    const unsigned int SCR_HEIGHT1 = mode->height;

    GLFWwindow* window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
        glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "My Title",
        glfwGetPrimaryMonitor(), nullptr);


    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    string diffuseMapPath = "grass1.jpg";
    string specularMapPath = "grass_spec.jpeg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 10.0f, 10.0f);
    
    string diffuseMapPath_road = "road1.jpg";
    string specularMapPath_road = "whiteBackground.png";
    unsigned int diffMap_road = loadTexture(diffuseMapPath_road.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap_road = loadTexture(specularMapPath_road.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_road = Cube(diffMap_road, specMap_road, 32.0f, 0.0f, 0.0f, 1.0, 12.0f);

    string diffuseMapPath_road1 = "road4.jpg";
    string specularMapPath_road1 = "whiteBackground.png";
    unsigned int diffMap_road1 = loadTexture(diffuseMapPath_road1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap_road1 = loadTexture(specularMapPath_road1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_road1 = Cube(diffMap_road1, specMap_road1, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath_brickWall = "brick.jpg";
    string specularMapPath_brickWall = "black_background.jpg";
    unsigned int diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_brickWall = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath_brickWall = "wooden_background1.jpg";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_woodPlatform = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 1.2, 1.0f);

    
    /*
    
    

    

    
*/
    diffuseMapPath_brickWall = "dark_brick.png";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_dark_brick = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 2.0, 0.5);

    
    diffuseMapPath_brickWall = "stone.jpeg";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_stone = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 0.5, 1.2);


    diffuseMapPath_brickWall = "oak.jpeg";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT);
    specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT);
    Cube cube_oak = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 2.0, 1.2f);

    diffuseMapPath_brickWall = "innerWall.jpg";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT);
    specMap_brickWall = loadTexture(specularMapPath_road.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT);
    Cube cube_innerWall = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 1.0, 1.0);

    diffuseMapPath_brickWall = "grey_brick.jpeg";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_grey_brick = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 2, 1.3);
    
    diffuseMapPath_brickWall = "cafe_sign.jpeg";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_cafe_sign = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 1.0, 1.0);

    diffuseMapPath_brickWall = "window.png";
    diffMap_brickWall = loadTexture(diffuseMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap_brickWall = loadTexture(specularMapPath_brickWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_window = Cube(diffMap_brickWall, specMap_brickWall, 32.0f, 0.0f, 0.0f, 1.0, 1.0);

    Cylinder cylinder = Cylinder(0.5f,36,18,glm::vec3(0.439, 0.071, 0.027),glm::vec3(0.439, 0.071, 0.027),glm::vec3(0.5f, 0.5f, 0.5f),32.0f);
    Cylinder white_cylinder = Cylinder(0.5f, 36, 18, glm::vec3(0.749, 0.725, 0.714), glm::vec3(0.749, 0.725, 0.714), glm::vec3(0.5f, 0.5f, 0.5f), 25.0f);

    Sphere sphere = Sphere(1.0f, 36, 18, glm::vec3(0.047, 0.6, 0.051), glm::vec3(0.047, 0.6, 0.051), glm::vec3(0.5f, 0.5f, 0.5f), 32.0);

    //holed cube
    float h_cube_z = -0.3, h_cube_x1 = 1.0, h_cube_x2 = 0.5, h_cube_y1 = 1.0, h_cube_y2 = 0.5;
    vector<unsigned int> h_cube_ind;

    float h_cube_outer[] = {
        
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f

    };
    //cout << sizeof(h_cube_outer) / sizeof(h_cube_outer[0]) - (12 * 3) << endl;
    /*
    ,
        -h_cube_x1, h_cube_y1, 0.0, 0.0, 1.0, 0.0,
        h_cube_x1, h_cube_y1, 0.0, 0.0, 1.0, 0.0,
        h_cube_x1, h_cube_y1, h_cube_z, 0.0, 1.0, 0.0,
        -h_cube_x1, h_cube_y1, h_cube_z, 0.0, 1.0, 0.0

        h_cube_x1, h_cube_y1, h_cube_z, 0.0, 1.0, 0.0,
        -h_cube_x1, h_cube_y1, h_cube_z, 0.0, 1.0, 0.0,
        h_cube_x1, h_cube_y1, 0.0, 0.0, 1.0, 0.0,

        h_cube_x1, h_cube_y1, h_cube_z, 1.0, 0.0, 0.0,
        h_cube_x1, h_cube_y1, 0.0, 1.0, 0.0, 0.0,
        h_cube_x1, -h_cube_y1, 0.0, 1.0, 0.0, 0.0,

        h_cube_x1, h_cube_y1, h_cube_z, 1.0, 0.0, 0.0,
        h_cube_x1, -h_cube_y1, 0.0, 1.0, 0.0, 0.0,
        h_cube_x1, -h_cube_y1, h_cube_z, 1.0, 0.0, 0.0
        for (int i = 0; i < ((sizeof(h_cube_outer) / sizeof(h_cube_outer[0])) - (12 * 3))/3; i++) {
        h_cube_ind.push_back(i);
    }*/
    h_cube_ind.push_back(0);
    h_cube_ind.push_back(1);
    h_cube_ind.push_back(2);

    h_cube_ind.push_back(2);
    h_cube_ind.push_back(3);
    h_cube_ind.push_back(0);

    unsigned int ind[] = {
        0, 1, 2
    };
    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    
    vector<unsigned int> circInd, circInd1, circInd2, circInd1t;
    float r1 = 4, r2 = 3.5, x1, y1, z1, x2, y2, z2, x3, y3, z3, z=-0.3;
    float theta = 25, c=0, t=6, k = 2 * pi;
    /*while (theta <= 180) {
        x1 = r2 * cosf(k* theta);
        y1 = -r2 * sinf(k*theta);
        z1 = 0.0;
        circVer.push_back(x1);
        circVer.push_back(y1);
        circVer.push_back(z1);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circInd.push_back(c);

        c++;
        x2 = r1 * cosf(k*theta);
        y2 = -r1 * sinf(k*theta);
        z2 = 0.0;
        circVer.push_back(x2);
        circVer.push_back(y2);
        circVer.push_back(z2);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circInd.push_back(c);

        c++;
        x3 = r1 * cosf(k*(theta+t));
        y3 = -r1 * sinf(k*(theta+t));
        z3 = 0.0;
        circVer.push_back(x3);
        circVer.push_back(y3);
        circVer.push_back(z3);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circInd.push_back(c);

        //2nd tri
        x1 = r2 * cosf(k*theta);
        y1 = -r2 * sinf(k*theta);
        z1 = 0.0;
        circVer.push_back(x1);
        circVer.push_back(y1);
        circVer.push_back(z1);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circInd.push_back(c);

        c++;
        x2 = r2 * cosf(k* (theta+t));
        y2 = -r2 * sinf(k *(theta+t));
        z2 = 0.0;
        circVer.push_back(x2);
        circVer.push_back(y2);
        circVer.push_back(z2);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circInd.push_back(c);

        c++;
        x3 = r1 * cosf(k * (theta + t));
        y3 = -r1 * sinf(k * (theta + t));
        z3 = 0.0;
        circVer.push_back(x3);
        circVer.push_back(y3);
        circVer.push_back(z3);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circInd.push_back(c);

        theta = theta + t;
    }*/
    int steps = 100, i;
    //float total = (((155 - 25) * 3.1416) / 180)/steps;
    float angle = 3.1416 * 2.0 / steps, starting = 26;
    for (i = 0; i < steps; i++) {
        x1 = r2 * cosf(starting +angle * i);
        y1 = r2 * sinf(starting +angle * i);
        z1 = 0.0;
        circVer.push_back(x1);
        circVer.push_back(y1);
        circVer.push_back(z1);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circVer1.push_back(x1);
        circVer1.push_back(y1);
        circVer1.push_back(z);
        circVer1.push_back(0.0);
        circVer1.push_back(0.0);
        circVer1.push_back(z);

        circInd.push_back(c);

        c++;
        x2 = r1 * cosf(starting +angle * i);
        y2 = r1 * sinf(starting +angle * i);
        z2 = 0.0;
        circVer.push_back(x2);
        circVer.push_back(y2);
        circVer.push_back(z2);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circVer1.push_back(x2);
        circVer1.push_back(y2);
        circVer1.push_back(z);
        circVer1.push_back(0.0);
        circVer1.push_back(0.0);
        circVer1.push_back(z);

        circInd.push_back(c);

        c++;
        x3 = r1 * cosf(starting +angle * (i+1));
        y3 = r1 * sinf(starting +angle * (i + 1));
        z3 = 0.0;
        circVer.push_back(x3);
        circVer.push_back(y3);
        circVer.push_back(z3);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circVer1.push_back(x3);
        circVer1.push_back(y3);
        circVer1.push_back(z);
        circVer1.push_back(0.0);
        circVer1.push_back(0.0);
        circVer1.push_back(z);

        circInd.push_back(c);
        c++;

        //2nd tri
        x1 = r2 * cosf(starting +angle * i);
        y1 = r2 * sinf(starting +angle * i);
        z1 = 0.0;
        circVer.push_back(x1);
        circVer.push_back(y1);
        circVer.push_back(z1);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circVer1.push_back(x1);
        circVer1.push_back(y1);
        circVer1.push_back(z);
        circVer1.push_back(0.0);
        circVer1.push_back(0.0);
        circVer1.push_back(z);

        circInd.push_back(c);

        c++;
        x2 = r2 * cosf(starting +angle * (i + 1));
        y2 = r2 * sinf(starting +angle * (i + 1));
        z2 = 0.0;
        circVer.push_back(x2);
        circVer.push_back(y2);
        circVer.push_back(z2);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circVer1.push_back(x2);
        circVer1.push_back(y2);
        circVer1.push_back(z);
        circVer1.push_back(0.0);
        circVer1.push_back(0.0);
        circVer1.push_back(z);

        circInd.push_back(c);

        c++;
        x3 = r1 * cosf(starting +angle * (i + 1));
        y3 = r1 * sinf(starting +angle * (i + 1));
        z3 = 0.0;
        circVer.push_back(x3);
        circVer.push_back(y3);
        circVer.push_back(z3);
        circVer.push_back(0.0);
        circVer.push_back(0.0);
        circVer.push_back(1.0);

        circVer1.push_back(x3);
        circVer1.push_back(y3);
        circVer1.push_back(z);
        circVer1.push_back(0.0);
        circVer1.push_back(0.0);
        circVer1.push_back(z);

        circInd.push_back(c);
        c++;
    }
    
    c = 0;
    glm::vec3 c12, c13, C12, C13, normal;
   
    for (i = 0; i < steps; i++) {
        
        x1 = r1 * cosf(starting + angle * i);
        y1 = r1 * sinf(starting + angle * i);
        z1 = 0.0;

        x2 = r1 * cosf(starting + angle * (i + 1));
        y2 = r1 * sinf(starting + angle * (i + 1));
        z2 = z;
        
        x3 = r1 * cosf(starting + angle * i);
        y3 = r1 * sinf(starting + angle * i);
        z3 = z;

        float ex1 = x2 - x1;
        float ey1 = y2 - y1;
        float ez1 = z2 - z1;
        float ex2 = x3 - x1;
        float ey2 = y3 - y1;
        float ez2 = z3 - z1;

        // cross product: e1 x e2
        float nx = ey1 * ez2 - ez1 * ey2;
        float ny = ez1 * ex2 - ex1 * ez2;
        float nz = ex1 * ey2 - ey1 * ex2;

        // normalize only if the length is > 0
        float length = sqrtf(nx * nx + ny * ny + nz * nz);
        float lengthInv = 1.0f / length;
        vector<float> normal1(3, 0.0f);
        normal1[0] = nx * lengthInv;
        normal1[1] = ny * lengthInv;
        normal1[2] = nz * lengthInv;
        
        c12.x = x2 - x1;
        c12.y = y2 - y1;
        c12.z = z2 - z1;

        C12 = glm::normalize(c12);

        c13.x = x3 - x1;
        c13.y = y3 - y1;
        c13.z = z3 - z1;

        C13 = glm::normalize(c13);

        normal = glm::normalize(glm::cross(C13, C12));

        circR1t.push_back(x1);
        circR1t.push_back(y1);
        circR1t.push_back(z1);
        
        circR1t.push_back(normal1[0]);
        circR1t.push_back(normal1[1]);
        circR1t.push_back(normal1[2]);
        circInd1t.push_back(c);
        c++;

        circR1t.push_back(x2);
        circR1t.push_back(y2);
        circR1t.push_back(z2);
        circR1t.push_back(normal1[0]);
        circR1t.push_back(normal1[1]);
        circR1t.push_back(normal1[2]);
        circInd1t.push_back(c);
        c++;

        circR1t.push_back(x3);
        circR1t.push_back(y3);
        circR1t.push_back(z3);
        circR1t.push_back(normal1[0]);
        circR1t.push_back(normal1[1]);
        circR1t.push_back(normal1[2]);
        circInd1t.push_back(c);
        c++;

        //2nd tri
        x3 = r1 * cosf(starting + angle * (i+1));
        y3 = r1 * sinf(starting + angle * (i+1));
        z3 = 0.0;

        c12.x = x1 - x2;
        c12.y = y1 - y2;
        c12.z = z1 - z2;

        C12 = glm::normalize(c12);

        c13.x = x3 - x2;
        c13.y = y3 - y2;
        c13.z = z3 - z2;

        C13 = glm::normalize(c13);

        normal = glm::normalize(glm::cross(C13, C12));

        ex1 = x2 - x1;
        ey1 = y2 - y1;
        ez1 = z2 - z1;
        ex2 = x3 - x1;
        ey2 = y3 - y1;
        ez2 = z3 - z1;

        // cross product: e1 x e2
        nx = ey1 * ez2 - ez1 * ey2;
        ny = ez1 * ex2 - ex1 * ez2;
        nz = ex1 * ey2 - ey1 * ex2;

        // normalize only if the length is > 0
        length = sqrtf(nx * nx + ny * ny + nz * nz);
        lengthInv = 1.0f / length;
        //vector<float> normal1(3, 0.0f);
        normal1[0] = nx * lengthInv;
        normal1[1] = ny * lengthInv;
        normal1[2] = nz * lengthInv;

                circR1t.push_back(x1);
        circR1t.push_back(y1);
        circR1.push_back(z1);
        
        circR1t.push_back(normal1[0]);
        circR1t.push_back(normal1[1]);
        circR1t.push_back(normal1[2]);
        circInd1t.push_back(c);
        c++;

        circR1t.push_back(x2);
        circR1t.push_back(y2);
        circR1t.push_back(z2);
        circR1t.push_back(normal1[0]);
        circR1t.push_back(normal1[1]);
        circR1t.push_back(normal1[2]);
        circInd1t.push_back(c);
        c++;

        circR1t.push_back(x3);
        circR1t.push_back(y3);
        circR1t.push_back(z3);
        circR1t.push_back(normal1[0]);
        circR1t.push_back(normal1[1]);
        circR1t.push_back(normal1[2]);
        circInd1t.push_back(c);
        c++;
    }
    c = 0;
    steps = 100;
    angle = 3.1416 * 2.0 / steps;
    i = 0;
    for (i = 0; i < steps; i++) {
        x1 = r1 * cosf(starting + angle * i);
        y1 = r1 * sinf(starting + angle * i);
        z1 = 0.0;
        circR1.push_back(x1);
        circR1.push_back(y1);
        circR1.push_back(z1);
        circR1.push_back(0.0);
        circR1.push_back(0.0);
        circR1.push_back(1.0);

        circInd1.push_back(c);

        c++;
        x2 = r1 * cosf(starting + angle * i);
        y2 = r1 * sinf(starting + angle * i);
        z2 = -0.3;
        circR1.push_back(x2);
        circR1.push_back(y2);
        circR1.push_back(z2);
        circR1.push_back(0.0);
        circR1.push_back(0.0);
        circR1.push_back(1.0);


        circInd1.push_back(c);

        c++;
        x3 = r1 * cosf(starting + angle * (i + 1));
        y3 = r1 * sinf(starting + angle * (i + 1));
        z3 = 0.0;
        circR1.push_back(x3);
        circR1.push_back(y3);
        circR1.push_back(z3);
        circR1.push_back(0.0);
        circR1.push_back(0.0);
        circR1.push_back(1.0);

        circInd1.push_back(c);
        c++;

        x1 = x2;
        y1 = y2;
        z1 = z2;
        circR1.push_back(x1);
        circR1.push_back(y1);
        circR1.push_back(z1);
        circR1.push_back(0.0);
        circR1.push_back(0.0);
        circR1.push_back(1.0);

        circInd1.push_back(c);

        c++;
        x2 = x3;
        y2 = y3;
        z2 = z3;
        circR1.push_back(x2);
        circR1.push_back(y2);
        circR1.push_back(z2);
        circR1.push_back(0.0);
        circR1.push_back(0.0);
        circR1.push_back(1.0);


        circInd1.push_back(c);

        c++;
        x3 = r1 * cosf(starting + angle * (i + 1));
        y3 = r1 * sinf(starting + angle * (i + 1));
        z3 = z;
        circR1.push_back(x3);
        circR1.push_back(y3);
        circR1.push_back(z3);
        circR1.push_back(0.0);
        circR1.push_back(0.0);
        circR1.push_back(1.0);

        circInd1.push_back(c);
        c++;
    }
    
    //low
    c = 0;
    steps = 100;
    angle = 3.1416 * 2.0 / steps;
    i = 0;
    for (i = 0; i < steps; i++) {
        x1 = r2 * cosf(starting + angle * i);
        y1 = r2 * sinf(starting + angle * i);
        z1 = 0.0;
        circR2.push_back(x1);
        circR2.push_back(y1);
        circR2.push_back(z1);
        circR2.push_back(0.0);
        circR2.push_back(0.0);
        circR2.push_back(1.0);

        circInd2.push_back(c);

        c++;
        x2 = r2 * cosf(starting + angle * i);
        y2 = r2 * sinf(starting + angle * i);
        z2 = -0.3;
        circR2.push_back(x2);
        circR2.push_back(y2);
        circR2.push_back(z2);
        circR2.push_back(0.0);
        circR2.push_back(0.0);
        circR2.push_back(1.0);


        circInd2.push_back(c);

        c++;
        x3 = r2 * cosf(starting + angle * (i + 1));
        y3 = r2 * sinf(starting + angle * (i + 1));
        z3 = 0.0;
        circR2.push_back(x3);
        circR2.push_back(y3);
        circR2.push_back(z3);
        circR2.push_back(0.0);
        circR2.push_back(0.0);
        circR2.push_back(1.0);

        circInd2.push_back(c);
        c++;

        x1 = x2;
        y1 = y2;
        z1 = z2;
        circR2.push_back(x1);
        circR2.push_back(y1);
        circR2.push_back(z1);
        circR2.push_back(0.0);
        circR2.push_back(0.0);
        circR2.push_back(1.0);

        circInd2.push_back(c);

        c++;
        x2 = x3;
        y2 = y3;
        z2 = z3;
        circR2.push_back(x2);
        circR2.push_back(y2);
        circR2.push_back(z2);
        circR2.push_back(0.0);
        circR2.push_back(0.0);
        circR2.push_back(1.0);


        circInd2.push_back(c);

        c++;
        x3 = r2 * cosf(starting + angle * (i + 1));
        y3 = r2 * sinf(starting + angle * (i + 1));
        z3 = z;
        circR2.push_back(x3);
        circR2.push_back(y3);
        circR2.push_back(z3);
        circR2.push_back(0.0);
        circR2.push_back(0.0);
        circR2.push_back(1.0);

        circInd2.push_back(c);
        c++;
    }
    
    
    /*for (i = 0; i < steps; i++) {

        x1 = r1 * cosf(starting + angle * i);
        y1 = r1 * sinf(starting + angle * i);
        z1 = z;

        x3 = r1 * cosf(starting + angle * (i + 1));
        y3 = r1 * sinf(starting + angle * (i + 1));
        z3 = 0.0;

        x2 = r1 * cosf(starting + angle * i);
        y2 = r1 * sinf(starting + angle * i);
        z2 = 0.0;
        cout << x1 << endl;
        cout << y1 << endl;
        cout << z1 << endl;

        cout << x2 << endl;
        cout << y2 << endl;
        cout << z2 << endl;

        cout << x3 << endl;
        cout << y3 << endl;
        cout << z3 << endl;
        float ex1 = x2 - x1;
        float ey1 = y2 - y1;
        float ez1 = z2 - z1;
        float ex2 = x3 - x1;
        float ey2 = y3 - y1;
        float ez2 = z3 - z1;

        // cross product: e1 x e2
        float nx = ( ey1 * ez2 - ez1 * ey2);
        float ny = - ( ez1 * ex2 - ex1 * ez2);
        float nz = ex1 * ey2 - ey1 * ex2;

        // normalize only if the length is > 0
        float length = sqrtf(nx * nx + ny * ny + nz * nz);
        float lengthInv = 1.0f / length;
        vector<float> normal1(3, 0.0f);
        normal1[0] = nx/length ;
        normal1[1] = ny/length ;
        normal1[2] = nz/length ;
        c12.x = x2 - x1;
        c12.y = y2 - y1;
        c12.z = z2 - z1;

        C12 = glm::normalize(c12);

        c13.x = x3 - x1;
        c13.y = y3 - y1;
        c13.z = z3 - z1;

        C13 = glm::normalize(c13);

        normal = glm::normalize(glm::cross(C13, C12));

        circR1.push_back(x1);
        circR1.push_back(y1);
        circR1.push_back(z1);
        circR1.push_back(0.0);
        circR1.push_back(1.0);
        circR1.push_back(0.0);
        //circR1.push_back(normal1[0]);
        //circR1.push_back(normal1[1]);
        //circR1.push_back(normal1[2]);
        circInd1.push_back(c);
        c++;

        circR1.push_back(x2);
        circR1.push_back(y2);
        circR1.push_back(z2);
        circR1.push_back(0.0);
        circR1.push_back(1.0);
        circR1.push_back(0.0);
        //circR1.push_back(normal1[0]);
        //circR1.push_back(normal1[1]);
        //circR1.push_back(normal1[2]);
        
        circInd1.push_back(c);
        c++;

        circR1.push_back(x3);
        circR1.push_back(y1);
        circR1.push_back(z3);
        circR1.push_back(0.0);
        circR1.push_back(1.0);
        circR1.push_back(0.0);
        //circR1.push_back(normal1[0]);
        //circR1.push_back(normal1[1]);
        //circR1.push_back(normal1[2]);
        circInd1.push_back(c);
        c++;

    }*/
    
    //float ver[] = {};
    //cout << c << endl;

    //float rc1 = sqrt(2);
    //cout << floor(cosf((3.1416 * (90+45)) / 180)) << endl;

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int signVAO, signVBO, signEBO, signVBO1, signEBO1, signVAO1, signVBO2, signEBO2, signVAO2, signVBO3, signEBO3, signVAO3;
    glGenVertexArrays(1, &signVAO);
    glGenBuffers(1, &signVBO);
    glGenBuffers(1, &signEBO);

    glBindVertexArray(signVAO);

    glBindBuffer(GL_ARRAY_BUFFER, signVBO);
    glBufferData(GL_ARRAY_BUFFER, circVer.size(), circVer.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, signEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, circInd.size(), circInd.data(), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &signVAO1);
    glGenBuffers(1, &signVBO1);
    glGenBuffers(1, &signEBO1);

    glBindVertexArray(signVAO1);

    glBindBuffer(GL_ARRAY_BUFFER, signVBO1);
    glBufferData(GL_ARRAY_BUFFER, circVer1.size(), circVer1.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, signEBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, circInd.size(), circInd.data(), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &signVAO2);
    glGenBuffers(1, &signVBO2);
    glGenBuffers(1, &signEBO2);

    glBindVertexArray(signVAO2);

    glBindBuffer(GL_ARRAY_BUFFER, signVBO2);
    glBufferData(GL_ARRAY_BUFFER, circR1.size(), circR1.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, signEBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, circInd1.size(), circInd1.data(), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &signVAO3);
    glGenBuffers(1, &signVBO3);
    glGenBuffers(1, &signEBO3);

    glBindVertexArray(signVAO3);

    glBindBuffer(GL_ARRAY_BUFFER, signVBO3);
    glBufferData(GL_ARRAY_BUFFER, circR2.size(), circR2.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, signEBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, circInd2.size(), circInd2.data(), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //h cube
    unsigned int cubeVAO1, cubeVBO1, cubeEBO1;
    glGenVertexArrays(1, &cubeVAO1);
    glGenBuffers(1, &cubeVBO1);
    glGenBuffers(1, &cubeEBO1);

    glBindVertexArray(cubeVAO1);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO1);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(h_cube_outer) / sizeof(h_cube_outer[0])), h_cube_outer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, h_cube_ind.size(), h_cube_ind.data(), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    
    i = 0;

    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        //GLint lightDirPos = glGetUniformLocation(lightingShader.ID, "light.direction");
        //glUniform3f(lightDirPos, -0.2f, -1.0f, -0.3f);
        //directionalLight.setUpDirectionalLight(lightingShader);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);


        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);
        
        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, t, r, s, ms1;
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        model = rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //bed(cubeVAO, lightingShader, model);
        
        lampStand(cubeVAO, lightingShader, model, 25.0, 0.0, -24.0);
        //floor(cubeVAO, lightingShader, model);
        
        drawCube(cubeVAO1, lightingShader, model, 1.0, 1.0, 1.0);

        welcomeSign(ourShader, signVAO, signVAO1, signVAO2, signVAO3, lightingShader, model, 0.929, 0.855, 0);

        translateMatrix = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        ms1 = translateMatrix * rotateXMatrix ;
        swing(cubeVAO, lightingShader,cylinder, model, ms1);
        
        if (rotateAngle_X <= 50.0 && farest == 0 ) {
            swingRotateI();
        }
        else {
            swingRotateB();
        }
        //swingRotateF();
        
        /*i = 1;
        if (i == 0) {
            swingRotateI();
            i++;
        }
        else {
            if (i == 1) {
                swingRotateB();
                i++;
            }
            else {
                swingRotateF();
                i--;
            }
        }*/

        if (swingF) {
            if (rotateAngle_X <= 60.0) {
                swingRotateI();
                swingF = 0;
            }
            //swingRotateI();
            
        }
        if (swingB) {
            swingRotateB();
            swingB = 0;
        }
        
        float building_move_x = 1 + 1.5 + 0.5, building_move_z = -6 - 1.5 - 1.7;
        model = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(building_move_x, 0.0, building_move_z));
        model = t;
        //building(cubeVAO, lightingShader, cube_brickWall, lightingShaderWithTexture, model, 0.545, 0, 0, 0.706, 0.592, 0.89);

        building_move_z = building_move_z - 2 - 0.5;
        model = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(building_move_x, 0.0, building_move_z));
        r = glm::mat4(1.0);
        r = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = t * r;
        //building(cubeVAO, lightingShader, cube_brickWall, lightingShaderWithTexture, model, 0, 1, 0.765, 0.753, 0.922, 0.882);
        //block 3

        
        
        glm::mat4 modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(-.2, 0.0, 11.0f));
        s = glm::scale(model, glm::vec3(.07, .17, 0.07));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);


        modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(-4.2, 0.0, 11.0f));
        s = glm::scale(model, glm::vec3(.07, .15, 0.07));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);

        //tree
        //front 3 right
        glm::mat4 modelForSphere1 = glm::mat4(1.0f);
        modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(5.0, 0.0, 9.0f));
        s = glm::scale(model, glm::vec3(.4, 0.06, 0.4));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(8.0, 2.0, -2.7f));
        modelForSphere1 = t;
        sphere.drawSphere(lightingShader, modelForSphere1);

        modelForSphere1 = glm::mat4(1.0f);
        modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(3.0, 0.0, 9.0f));
        s = glm::scale(model, glm::vec3(.4, 0.06, 0.4));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(6.0, 2.0, -2.7f));
        modelForSphere1 = t;
        sphere.drawSphere(lightingShader, modelForSphere1);

        modelForSphere1 = glm::mat4(1.0f);
        modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(1.0, 0.0, 9.0f));
        s = glm::scale(model, glm::vec3(.4, 0.06, 0.4));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(4.0, 2.0, -2.7f));
        modelForSphere1 = t;
        sphere.drawSphere(lightingShader, modelForSphere1);

        //back 3 right
        modelForSphere1 = glm::mat4(1.0f);
        modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(5.0, 0.0, 7.0f));
        s = glm::scale(model, glm::vec3(.4, 0.06, 0.4));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(8.0, 2.0, -4.7f));
        modelForSphere1 = t;
        sphere.drawSphere(lightingShader, modelForSphere1);

        modelForSphere1 = glm::mat4(1.0f);
        modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(3.0, 0.0, 7.0f));
        s = glm::scale(model, glm::vec3(.4, 0.06, 0.4));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(6.0, 2.0, -4.7f));
        modelForSphere1 = t;
        sphere.drawSphere(lightingShader, modelForSphere1);

        modelForSphere1 = glm::mat4(1.0f);
        modelForSphere = glm::mat4(1.0f);
        s = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(1.0, 0.0, 7.0f));
        s = glm::scale(model, glm::vec3(.4, 0.06, 0.4));
        modelForSphere = t * s;
        cylinder.drawSphere(lightingShader, modelForSphere);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(4.0, 2.0, -4.7f));
        modelForSphere1 = t;
        sphere.drawSphere(lightingShader, modelForSphere1);

        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.



        glBindVertexArray(lightCubeVAO);

        /*
        for (unsigned int i = 1; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }*/

        //
        //model = glm::mat4(1.0f);
        
        //drawtri(signVAO, lightingShader, model, 0.945, 0.98, 0.157);

        model = glm::mat4(1.0f);
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lampPost(ourShader, cubeVAO, lightingShader, model, 0.8f, 0.8f, 0.8f);
        lampPost(ourShader, cubeVAO, lightingShader, model, 0.8f, 0.8f, 0.8f);
        //securityLight(ourShader, cubeVAO, lightingShader, model, 0.929, 0.855, 0);
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        lightingShaderWithTexture.use();
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(model, glm::vec3(-0.5f, 1.2f, -1.0f));
        block(modelMatrixForContainer, lightingShaderWithTexture, cube);

        roads(cubeVAO, lightingShader, cube_road, lightingShaderWithTexture, cube_road1);

        building_move_x = 1 + 1.5 + 0.5, building_move_z = -6 - 1.5 - 1.7;
        model = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(building_move_x, 0.0, building_move_z));
        model = t;
        building(cubeVAO, lightingShader, cube_brickWall, cube_woodPlatform, lightingShaderWithTexture, model, 0.545, 0, 0, 0.706, 0.592, 0.89);

        building_move_z = building_move_z - 2 - 0.5;
        model = glm::mat4(1.0f);
        t = glm::mat4(1.0f);
        t = glm::translate(identityMatrix, glm::vec3(building_move_x, 0.0, building_move_z));
        r = glm::mat4(1.0);
        r = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = t * r;
        building(cubeVAO, lightingShader, cube_brickWall, cube_woodPlatform, lightingShaderWithTexture, model, 0, 1, 0.765, 0.753, 0.922, 0.882);
        //block 3
        float block_width = 6;
        float road_width = 1.5;
        float pos = -block_width - road_width - 1;
        float block_x = 7.5;
        restaurant(cube_cafe_sign, cube_dark_brick, cube_stone, cube_oak, cube_innerWall, cube_grey_brick, lightingShaderWithTexture, cubeVAO, lightingShader, model, -block_x + road_width, pos);
        pos = -block_width - road_width - 1 - road_width - 0.3 - block_width;
        school(white_cylinder, cube_window, cube_grey_brick, lightingShaderWithTexture, cubeVAO, lightingShader, -block_x + road_width, pos);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
void drawtri(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f, int n = 1.0)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, 0);
}

void swing(unsigned int& cubeVAO, Shader& lightingShader, Cylinder& cylinder, glm::mat4 model = glm::mat4(1.0f), glm::mat4 ms1 = glm::mat4(1.0f))
{
    glm::mat4 model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), rotate = glm::mat4(1.0f),
        all = glm::mat4(1.0f), t =glm::mat4(1.0f), r = glm::mat4(1.0f), trans1 = glm::mat4(1.0f);
    r = glm::rotate(model1, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    all = r;
    translate = glm::translate(model1, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model1, glm::vec3(2, 0.05, 1.0));
    trans1 = glm::translate(model1, glm::vec3(-1.0, 2.1, -0.5));

    model1 = all * trans1 * scale;
    drawCube(cubeVAO, lightingShader, model1, 1.0, 0.0, 0.0);

    float x = 0.5 + (0.5 / 2);
    scale = glm::mat4(1.0f);
    trans1 = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    model1 = glm::mat4(1.0f);
    translate = glm::translate(model1, glm::vec3(-0.5, -0.5, -0.5));
    trans1 = glm::translate(model1, glm::vec3(-x, 2.3, 0));
    scale = glm::scale(model1, glm::vec3(.01, -0.08, 0.01));
    model1 =all *  trans1 * model * scale;
    cylinder.drawSphere(lightingShader, model1);

    x =(0.5 / 2);
    scale = glm::mat4(1.0f);
    trans1 = glm::mat4(1.0f);
    model1 = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate = glm::translate(model1, glm::vec3(-0.5, -0.5, -0.5));
    trans1 = glm::translate(model1, glm::vec3(-x, 2.3, 0));
    scale = glm::scale(model1, glm::vec3(.01, -0.08, 0.01));
    //model1 = all * trans1 * scale * translate;
    model1 = all * trans1 * model *   scale;
    cylinder.drawSphere(lightingShader, model1);

    
    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f);
    translate = glm::translate(model1, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model1, glm::vec3(0.6, 0.03, 0.5));
    trans1 = glm::translate(model1, glm::vec3(-0.5, 0.75, 0));
    model1 = all * trans1 * ms1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model1, 1.0, 0.0, 0.0);

    //right swing

    rotate = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    x = 0.5 + (0.5 / 2);
    scale = glm::mat4(1.0f);
    trans1 = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    model1 = glm::mat4(1.0f);
    translate = glm::translate(model1, glm::vec3(-0.5, -0.5, -0.5));
    trans1 = glm::translate(model1, glm::vec3(x, 2.3, 0));
    scale = glm::scale(model1, glm::vec3(.01,- 0.08, 0.01));
    model1 = all *  trans1 * model * scale ;
    cylinder.drawSphere(lightingShader, model1);

    x = (0.5 / 2);
    scale = glm::mat4(1.0f);
    trans1 = glm::mat4(1.0f);
    model1 = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate = glm::translate(model1, glm::vec3(-0.5, -0.5, -0.5));
    trans1 = glm::translate(model1, glm::vec3(x, 2.3, 0));
    scale = glm::scale(model1, glm::vec3(.01, -0.08, 0.01));
    model1 = all *  trans1 * model * scale ;
    cylinder.drawSphere(lightingShader, model1);

    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f);
    translate = glm::translate(model1, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model1, glm::vec3(0.6, 0.03, 0.5));
    trans1 = glm::translate(model1, glm::vec3(0.5, 0.75, 0));
    model1 = all * trans1 * ms1 * scale * translate ;
    drawCube(cubeVAO, lightingShader, model1, 1.0, 0.0, 0.0);
}

void welcomeSign(Shader& ourShader, unsigned int& signVAO, unsigned int& signVAO1, unsigned int& signVAO2, unsigned int& signVAO3, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    glm::mat4 model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f);
    translate = glm::translate(model1, glm::vec3(1.1, 0, -0.5));
    scale = glm::scale(model1, glm::vec3(0.9, 1.0, 1.0));
    model1 =scale * translate;
    int n1 = circVer.size();
    drawtri(signVAO, lightingShader, model1, 0.945, 0.98, 0.157, n1);
    drawtri(signVAO1, lightingShader, model1, 0.945, 0.98, 0.157, n1);
        
    drawtri(signVAO2, lightingShader, model1, 0.945, 0.98, 0.157, circR1.size());
    drawtri(signVAO3, lightingShader, model1, 0.71, 0.741, 0.118, circR2.size());   
}
void centerWindow(unsigned int& cubeVAO, Shader& lightingShader, Cube& cube_woodPlatform, Shader& lightingShaderwithTex, glm::mat4 alTogether, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f, float floorX = 1.0f, float floorY = 1.0f, float floorZ = 1.0f, float windowHeight = 1.0f, float wall = 0.0)
{
    float midX = ((floorX / 2) / 2) / 2;
    float f2window1X = (((floorX / 2) / 2) + midX) * 2;
    float f2window1Y = 0.07;
    float f2window1Z = 0.3;

    float f2window2X = (f2window1X / 2) / 11;
    float f2window2Y = ((floorY / 2) * 3) / 4 + (floorY / 2) / 2;
    float f2window2Z = f2window1Z / 2;

    glm::mat4 scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    glm::mat4 rotate1 = glm::mat4(1.0f);
    if (wall == 0.0) {
        rotate1 = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else if (wall == 1.0) {
        //left
        rotate1 = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else if (wall == 2.0) {
        //right
        rotate1 = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    //
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(f2window1X, f2window1Y, f2window1Z));
    translate2 = glm::translate(model, glm::vec3(0.0, windowHeight + ((floorY / 2) - ((floorY / 2) * 3) / 4), (floorZ / 2) + (f2window1Z / 2)));
    model = alTogether * rotate1 * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.945, 0.98, 0.157);
    cube_woodPlatform.drawCubeWithTexture(lightingShaderwithTex, model);
    //
    rotate = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(f2window2X, f2window2Y, f2window2Z));
    translate2 = glm::translate(model, glm::vec3(-(f2window1X / 2 - (f2window2X / 2)), windowHeight + ((floorY / 2) - ((floorY / 2) * 3) / 4), (floorZ / 2) + (f2window2Z / 2)));
    model = alTogether * rotate1 * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.945, 0.98, 0.157);
    cube_woodPlatform.drawCubeWithTexture(lightingShaderwithTex, model);
    //
    rotate = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(f2window2X, f2window2Y, f2window2Z));
    translate2 = glm::translate(model, glm::vec3(0.0, windowHeight + ((floorY / 2) - ((floorY / 2) * 3) / 4), (floorZ / 2) + (f2window2Z / 2)));
    model = alTogether * rotate1 * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.945, 0.98, 0.157);
    cube_woodPlatform.drawCubeWithTexture(lightingShaderwithTex, model);
    //
    rotate = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(f2window2X, f2window2Y, f2window2Z));
    translate2 = glm::translate(model, glm::vec3((f2window1X / 2 - (f2window2X / 2)), windowHeight + ((floorY / 2) - ((floorY / 2) * 3) / 4), (floorZ / 2) + (f2window2Z / 2)));
    model = alTogether * rotate1 * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.945, 0.98, 0.157);
    cube_woodPlatform.drawCubeWithTexture(lightingShaderwithTex, model);
    //
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(f2window1X, f2window1Y, f2window1Z));
    translate2 = glm::translate(model, glm::vec3(0.0, (windowHeight + ((floorY / 2) - ((floorY / 2) * 3) / 4)) + (f2window2Y), (floorZ / 2) + (f2window1Z / 2)));
    model = alTogether * rotate1 * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.945, 0.98, 0.157);
    cube_woodPlatform.drawCubeWithTexture(lightingShaderwithTex, model);

    float insideX = f2window1X - f2window2X * 2;
    float insideY = f2window2Y;
    float insideZ = 0.0;
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(insideX, insideY, insideZ));
    translate2 = glm::translate(model, glm::vec3(0.0, windowHeight + ((floorY / 2) - ((floorY / 2) * 3) / 4), (floorZ / 2) + (f2window2Z / 2)));
    model = alTogether * rotate1 * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);
}

void door(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f, float floorX = 1.0f, float floorY = 1.0f, float floorZ = 1.0f, float wall = 0.0)
{
    float doorX = floorX / 4;
    float doorY = floorY - (floorY / 8);
    float doorZ = 0.02;

    glm::mat4 scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(doorX, doorY, doorZ));
    translate2 = glm::translate(model, glm::vec3(0, 0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //side bar
    //
    float sideX = doorX / 16;
    float sideY = doorY;
    float sideZ = 0.03;

    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(sideX, sideY, sideZ));
    translate2 = glm::translate(model, glm::vec3(-(doorX / 2), 0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.639, 0.294);

    //
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(sideX, sideY, sideZ));
    translate2 = glm::translate(model, glm::vec3((doorX / 2), 0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.639, 0.294);

    //mid
    float midX = doorX - sideX;
    float midY = sideX;
    float midZ = sideZ;

    //upper bar
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(midX, midY, midZ));
    translate2 = glm::translate(model, glm::vec3(0.0, doorY - (midY), floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.639, 0.294);

    //lower bar
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(midX, midY, midZ));
    translate2 = glm::translate(model, glm::vec3(0.0, 0.0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.8, 0.639, 0.294);

    //side of mid
    float mid1X = (doorX - sideX) / 4, mid1Y = doorY - midY, mid1Z = midZ;
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(mid1X, mid1Y, mid1Z));
    translate2 = glm::translate(model, glm::vec3(-(doorX / 2 - sideX) + mid1X / 4, 0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.259, 0.02, 0.02);

    //
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(mid1X, mid1Y, mid1Z));
    translate2 = glm::translate(model, glm::vec3((doorX / 2 - sideX) - mid1X / 4, 0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.259, 0.02, 0.02);

    //mid 2
    float mid2X = midX, mid2Y = (doorY - midY) / 8, mid2Z = midZ;
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(mid2X, mid2Y, mid2Z));
    translate2 = glm::translate(model, glm::vec3(0, doorY - (midY)-(mid2Y), floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.259, 0.02, 0.02);

    //mid 2
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(mid2X, mid2Y, mid2Z));
    translate2 = glm::translate(model, glm::vec3(0, 0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.259, 0.02, 0.02);

    //
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(doorX, doorY, doorZ + 0.005));
    translate2 = glm::translate(model, glm::vec3(0, 0, floorZ / 2));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.639, 0.227, 0.137);

}

void lampPost(Shader& ourShader, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    model = glm::translate(model, pointLightPositions[1]);
    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
    ourShader.setMat4("model", model);
    ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}
void securityLight(Shader& ourShader, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    model = glm::translate(model, pointLightPositions[2]);
    model = glm::scale(model, glm::vec3(0.09f)); // Make it a smaller cube
    ourShader.setMat4("model", model);
    ourShader.setVec3("color", glm::vec3(0.929, 0.855, 0));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}
void lampStand(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z)
{
    float standX = 0.06, standY = 2.0, standZ = 0.06;
    glm::mat4 model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), trans2 = glm::mat4(1.0f);
    //translate = glm::translate(model1, glm::vec3(0, 0, -25));
    trans2 = glm::translate(model1, glm::vec3(x, y, z));
    scale = glm::scale(model1, glm::vec3(standX, standY, standZ));
    model1 =  scale * trans2;
    drawCube(cubeVAO, lightingShader, model1, 0.024, 0.035, 0.259);
}

void building(unsigned int& cubeVAO, Shader& lightingShader, Cube& cube_brickWall, Cube& cube_woodPlatform, Shader& lightingShaderwithTex, glm::mat4 alTogether, float r1, float g1, float b1, float r2, float g2, float b2)
{
    float floor1X = 2.0;
    float floor1Y = 1.5;
    float floor1Z = 2.0;

    float midX = 2.05;
    float midY = 0.05;
    float midZ = floor1Z + 0.05;

    float floor2X = 1.9;
    float floor2Y = 1.4;
    float floor2Z = 1.9;

    float f2window1X = 1.76;
    float f2window1Y = 0.07;
    float f2window1Z = 0.3;

    float f2window2X = 0.07;
    float f2window2Y = floor2Y - 0.07 - 0.3;
    float f2window2Z = 0.2;

    //floor1
    glm::mat4 model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0.05, -0.5));
    scale = glm::scale(model, glm::vec3(floor1X, floor1Y, floor1Z));
    model = alTogether * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, r1, g1, b1);
    cube_brickWall.drawCubeWithTexture(lightingShaderwithTex, model);

    //mid
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0.06, -0.5));
    scale = glm::scale(model, glm::vec3(midX, midY, midZ));
    translate2 = glm::translate(model, glm::vec3(0.0, floor1Y, 0.0));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.412, 0.408, 0.376);

    //floor2
    model = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    scale = glm::scale(model, glm::vec3(floor2X, floor2Y, floor2Z));
    translate2 = glm::translate(model, glm::vec3(0.0, floor1Y + midY, 0.0));
    model = alTogether * translate2 * scale * translate;
    cube_brickWall.drawCubeWithTexture(lightingShaderwithTex, model);

    //floor2 window1
    float windowHeight = floor1Y + midY;
    model = glm::mat4(1.0f);
    centerWindow(cubeVAO, lightingShader, cube_woodPlatform, lightingShaderwithTex, alTogether, model, 0.945, 0.98, 0.157, floor2X, floor2Y, floor2Z, windowHeight, 0.0);

    model = glm::mat4(1.0f);
    centerWindow(cubeVAO, lightingShader, cube_woodPlatform, lightingShaderwithTex, alTogether, model, 0.945, 0.98, 0.157, floor2X, floor2Y, floor2Z, windowHeight, 1.0);

    model = glm::mat4(1.0f);
    centerWindow(cubeVAO, lightingShader, cube_woodPlatform, lightingShaderwithTex, alTogether, model, 0.945, 0.98, 0.157, floor2X, floor2Y, floor2Z, windowHeight, 2.0);

    model = glm::mat4(1.0f);
    door(cubeVAO, lightingShader, alTogether, model, 0.945, 0.98, 0.157, floor1X, floor1Y, floor1Z, 2.0);

}
void school(Cylinder& white_cylinder, Cube& cube_window, Cube& cube_grey_brick, Shader& lightingShaderwithTex, unsigned int& cubeVAO, Shader& lightingShader, float x1, float z1) {
    // left wing
    glm::mat4 all = glm::mat4(1.0f), r = glm::mat4(1.0f), t = glm::mat4(1.0f);
    r = glm::rotate(all, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::translate(all, glm::vec3(x1-1.5, 0, z1));
    all = t * r;
    float x = 2.0, y1 = 1.0, y2 = 0.05, y3 = 0.9, z = 1.5, w1x = 0.4, w1y = 0.6, w1z = 0.03;
    glm::mat4 model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, 0, 0.0));
    scale = glm::scale(model, glm::vec3(x, y1, z));
    model =all* translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 0.25, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 0.25, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 0.25, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model =all* translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1+y2, 0.0));
    scale = glm::scale(model, glm::vec3(x, y3, z));
    model =all* translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    //3
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1+y2+y3, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3 + y2, 0.0));
    scale = glm::scale(model, glm::vec3(x, y3, z));
    model = all * translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2+y3+y2+y3 , 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

    //front of school
    glm::mat4 all1 = glm::mat4(1.0f),t1 = glm::mat4(1.0f);
    
    t1 = glm::translate(all1, glm::vec3(x1, 0, z1-2-1.5));
    all1 = t1;
    all = glm::mat4(1.0f);
    x = 2.0, y1 = 1.0, y2 = 0.05, y3 = 0.9, z = 1.5, w1x = 0.4, w1y = 0.6, w1z = 0.03;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, 0, 0.0));
    scale = glm::scale(model, glm::vec3(x, y1, z));
    model =all1* all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 0.25, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 0.25, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    //door
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 0.1, 1.5));
    scale = glm::scale(model, glm::vec3(0.9, 0.8, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    //steps
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.4, 0.05, 1.5));
    scale = glm::scale(model, glm::vec3(1.0, 0.05, 0.5));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1, 1, 1);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.3, 0.0, 1.5));
    scale = glm::scale(model, glm::vec3(1.2, 0.05, 0.7));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.749, 0.725, 0.714);

    //hood
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.4, 0.9, 1.5));
    scale = glm::scale(model, glm::vec3(1.0, 0.05, 0.5));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1, 1, 1);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.44, 0, 1.8));
    scale = glm::scale(model, glm::vec3(0.05, 0.05, 0.05));
    model = all1 * all * translate * scale;
    white_cylinder.drawSphere(lightingShader, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(2.35, 0, 1.8));
    scale = glm::scale(model, glm::vec3(0.05, 0.05, 0.05));
    model = all1 * all * translate * scale;
    white_cylinder.drawSphere(lightingShader, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2, 0.0));
    scale = glm::scale(model, glm::vec3(x, y3, z));
    model = all1 * all * translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    //3
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3 + y2, 0.0));
    scale = glm::scale(model, glm::vec3(x, y3, z));
    model = all1 * all * translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3 + y2 + y3, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

    //front of school2

    all = glm::mat4(1.0f);
    t = glm::mat4(1.0f);
    t = glm::translate(all, glm::vec3(2.0, 0, 0.0));
    all = t;
    x = 2.0, y1 = 1.0, y2 = 0.05, y3 = 0.9, z = 1.5, w1x = 0.4, w1y = 0.6, w1z = 0.03;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, 0, 0.0));
    scale = glm::scale(model, glm::vec3(x, y1, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

    //door

    //window

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 0.25, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 0.25, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2, 0.0));
    scale = glm::scale(model, glm::vec3(x, y3, z));
    model = all1 * all * translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 1.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    //3
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3 + y2, 0.0));
    scale = glm::scale(model, glm::vec3(x, y3, z));
    model = all1 * all * translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //window
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.25, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.85, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.45, 2.2, 1.5));
    scale = glm::scale(model, glm::vec3(w1x, w1y, w1z));
    model = all1 * all * translate * scale;
    cube_window.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3 + y2 + y3, 0.0));
    scale = glm::scale(model, glm::vec3(x, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

    //left side
    all = glm::mat4(1.0f);
    t = glm::mat4(1.0f);
    t = glm::translate(all, glm::vec3(-1.5, 0, 0.0));
    all = t;
    x = 2.0, y1 = 1.0, y2 = 0.05, y3 = 0.9, z = 1.5, w1x = 0.4, w1y = 0.6, w1z = 0.03;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, 0, 0.0));
    scale = glm::scale(model, glm::vec3(z, y1, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

    

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1, 0.0));
    scale = glm::scale(model, glm::vec3(z, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2, 0.0));
    scale = glm::scale(model, glm::vec3(z, y3, z));
    model = all1 * all * translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //3
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3, 0.0));
    scale = glm::scale(model, glm::vec3(z, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.49, 0.161, 0.012);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3 + y2, 0.0));
    scale = glm::scale(model, glm::vec3(z, y3, z));
    model = all1 * all * translate * scale;
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, y1 + y2 + y3 + y2 + y3, 0.0));
    scale = glm::scale(model, glm::vec3(z, y2, z));
    model = all1 * all * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.902, 0.608, 0.059);

}
void floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float floor1X = 6.0;
    float floor1Y = -0.01;
    float floor1Z = 4.0;

    //floor1
    glm::mat4 model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f), rotate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.0, 0, 0.0));
    scale = glm::scale(model, glm::vec3(floor1X, floor1Y, floor1Z));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.471, 0.557, 0.631);



}

void roads(unsigned int& cubeVAO, Shader& lightingShader, Cube& cube_road, Shader& lightingShaderwithTex, Cube& cube_road1)
{
    float r = 0.0, g = 0.0, b = 1.0;
    float block_width = 6;//z axis
    float road_width = 1.5;
    //central road
    float central_len = block_width * 3 + road_width * 3;
    glm::mat4 model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f), trans = glm::mat4(1.0f), trans1 = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_width, 0.09, -central_len));
    model1 = scale;
    //drawCube(cubeVAO, lightingShader, model1, r, g, b);
    cube_road.drawCubeWithTexture(lightingShaderwithTex, model1);
    //most left road
    float block_x = 7.5;
    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_width, 0.09, -central_len));
    trans = glm::translate(model1, glm::vec3(block_x + road_width, 0, 0));
    model1 = trans * scale;
    drawCube(cubeVAO, lightingShader, model1, r, g, b);

    //most right road
    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_width, 0.09, -central_len));
    trans = glm::translate(model1, glm::vec3(-block_x - road_width, 0, 0));
    model1 = trans * scale;
    drawCube(cubeVAO, lightingShader, model1, r, g, b);


    
    //left side road
    float road_len1 = block_x + road_width;
    // 0
    road_len1 = block_x + road_width;
    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(-road_len1, 0, 0));
    model1 = trans * scale;
    drawCube(cubeVAO, lightingShader, model1, r, g, b);
    //1
    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(-road_len1, 0, -block_width));
    model1 = trans * scale;
    cube_road1.drawCubeWithTexture(lightingShaderwithTex, model1);
    //2
    model1 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    trans = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(-road_len1, 0, -block_width*2 - road_width));
    model1 = trans * scale;
    cube_road1.drawCubeWithTexture(lightingShaderwithTex, model1);
    //3
    model1 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    trans = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(-road_len1, 0, -block_width * 3 - road_width*2));
    model1 = trans * scale;
    cube_road1.drawCubeWithTexture(lightingShaderwithTex, model1);

    //right side road
    // 0
    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(road_width, 0, 0));
    model1 = trans * scale;
    drawCube(cubeVAO, lightingShader, model1, r, g, b);
    //1
    model1 = glm::mat4(1.0f), scale = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(road_width, 0, -block_width));
    model1 = trans * scale;
    cube_road1.drawCubeWithTexture(lightingShaderwithTex, model1);
    //2
    model1 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    trans = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(road_width, 0, -block_width * 2 - road_width));
    model1 = trans * scale;
    cube_road1.drawCubeWithTexture(lightingShaderwithTex, model1);
    //3
    model1 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    trans = glm::mat4(1.0f);
    scale = glm::scale(model1, glm::vec3(road_len1, 0.09, -road_width));
    trans = glm::translate(model1, glm::vec3(road_width, 0, -block_width * 3 - road_width * 2));
    model1 = trans * scale;
    cube_road1.drawCubeWithTexture(lightingShaderwithTex, model1);
}

void block(glm::mat4 modelMatrixForContainer, Shader& lightingShaderWithTexture, Cube& cube)
{
    
    float r = 0.0, g = 1.0, b = 0.0;
    float block_width = 6-1.5;//z axis
    float block_x = 7.5;
    glm::mat4 model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.5, 0, -1.5-block_width));
    scale = glm::scale(model, glm::vec3(block_x, 0.07, block_width));
    model = translate * scale;
    modelMatrixForContainer = model * modelMatrixForContainer;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);


    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(1.5, 0, (- 1.5 - 1.5 - block_width)*2));
    scale = glm::scale(model, glm::vec3(block_x, 0.07, block_width+1.5+1.5));
    model = translate * scale;
    modelMatrixForContainer = model * modelMatrixForContainer;
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

}


void restaurant(Cube& cube_cafe_sign, Cube& cube_dark_brick, Cube& cube_stone, Cube& cube_oak, Cube& cube_innerWall, Cube& cube_grey_brick, Shader& lightingShaderwithTex, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x1, float z1)
{

    
    glm::mat4 model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), 
        translate1 = glm::mat4(1.0f), all = glm::mat4(1.0f),
        t = glm::mat4(1.0f), r = glm::mat4(1.0f), translateR = glm::mat4(1.0f);
    t = glm::translate(model, glm::vec3(x1 , 2.6, z1-(1.8/2)));
    r = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    all = t*r;
    //3 ceiling
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(2, 0.1, 1.8));
    model = all * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 0.0, 0.0);
    cube_dark_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, 0.1, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(1.6, 0.1, 1.4));
    model = all * translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.0, 1.0, 0.0);
    cube_dark_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, 0.2, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(1.2, 0.1, 1.0));
    model =all * translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.0, 1.0, 0.0);
    cube_dark_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //2nd floor
    float c = (1.8 - 1.0) / 2;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -1.2/2, -c));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(1.8, 1.2, 1.0));
    model =all * translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 0.0);
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    c = (1.8 - 1.0) / 2;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -1.2 / 2, 0.2));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(1.6, 1.2, 0.1));
    model = all * translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);
    cube_innerWall.drawCubeWithTexture(lightingShaderwithTex, model);

    // left ppillar
    c = (1.8 / 2) - (0.8 / 2);
    float x = (1.8 / 2) - (0.2 / 2);
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(-x, -1.2 / 2, c));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(0.2, 1.18, 0.8));
    model =all* translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 0.0, 0.0);
    cube_stone.drawCubeWithTexture(lightingShaderwithTex, model);

    //right pillar
    x = (1.8 / 2) - (0.5 / 2);
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(x, -1.2 / 2, c));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(0.5, 1.18, 0.8));
    model =all* translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 0.0, 0.0);
    cube_oak.drawCubeWithTexture(lightingShaderwithTex, model);

    x = (1.8 / 2) - (0.5 / 2);
    
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(x, -1.2 / 2, 0.95));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(0.5, 0.5, 0.009));
    model = all * translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 0.0, 0.0);
    cube_cafe_sign.drawCubeWithTexture(lightingShaderwithTex, model);

    //ground
    c = (1.8 - 1.0) / 2;
    x = (1.3 / 2) + 1.2;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -x, 0.0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(2, 1.3, 1.8));
    model =all* translate1 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.0, 1.0, 1.0);
    cube_grey_brick.drawCubeWithTexture(lightingShaderwithTex, model);

    //relling most left
    float xR, yR, zR, shift;
    //upper
    shift = -0.59;
    xR = 0.2;
    yR = 0.1;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -0.8, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all* translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //bottom
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -1.15, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //left
    xR = 0.05;
    yR = 0.25;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(-0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //relling most left 2
    //upper
    shift = -0.39 + 0.01;
    xR = 0.2;
    yR = 0.1;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -0.8, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //bottom
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -1.15, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //left
    xR = 0.05;
    yR = 0.25;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(-0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //relling most left 3
    //upper
    shift = -0.18 + 0.01;
    xR = 0.2;
    yR = 0.1;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -0.8, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //bottom
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -1.15, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //left
    xR = 0.05;
    yR = 0.25;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(-0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //relling most left 4
    //upper
    shift = 0.03 + 0.01;
    xR = 0.2;
    yR = 0.1;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -0.8, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //bottom
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -1.15, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //left
    xR = 0.05;
    yR = 0.25;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(-0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //relling most left 5
    //upper
    shift = 0.24 + 0.015;
    xR = 0.2;
    yR = 0.1;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -0.8, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //bottom
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -1.15, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //left
    xR = 0.05;
    yR = 0.25;
    zR = 0.1;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(-0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0.075, -0.975, 0.85));
    translateR = glm::mat4(1.0f);
    translateR = glm::translate(model, glm::vec3(shift, 0, 0));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translateR * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    //light chair
    xR = 0.009;
    yR = 0.5;
    zR = 0.009;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0, -0.3, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(0.02, -0.3, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    xR = 0.02;
    yR = 0.009;
    zR = 0.009;
    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(xR/2, -0.3, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(xR / 2, -0.35, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(xR / 2, -0.25, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(xR / 2, -0.45, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(xR / 2, -0.22, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(xR / 2, -0.16, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f), scale = glm::mat4(1.0f), translate = glm::mat4(1.0f), translate1 = glm::mat4(1.0f);
    translate1 = glm::translate(model, glm::vec3(xR / 2, -0.1, 0.7));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, -0.5));
    scale = glm::scale(model, glm::vec3(xR, yR, zR));
    model = all * translate1 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

}


void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //blanket
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        swingF = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        swingB = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    
    /*if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        pointlight2.turnOff();
        pointlight3.turnOff();
        pointlight4.turnOff();

    }
    /*if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }

    }

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }*/

    /*if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        pointlight1.turnOn();
        pointlight2.turnOn();
        pointlight3.turnOn();
        pointlight4.turnOn();
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight2.turnAmbientOn();
        pointlight3.turnAmbientOn();
        pointlight4.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOff();
        pointlight2.turnAmbientOff();
        pointlight3.turnAmbientOff();
        pointlight4.turnAmbientOff();
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight2.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        pointlight4.turnDiffuseOn();
    }

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOff();
        pointlight2.turnDiffuseOff();
        pointlight3.turnDiffuseOff();
        pointlight4.turnDiffuseOff();
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOff();
        pointlight2.turnSpecularOff();
        pointlight3.turnSpecularOff();
        pointlight4.turnDiffuseOff();
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        pointlight1.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        pointlight1.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        pointlight2.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        pointlight2.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        pointlight3.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        pointlight3.turnOff();
    }*/
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

