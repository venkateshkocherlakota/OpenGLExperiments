#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "src/base.cpp"
#include "src/render_funcs.cpp"
#include "src/triangle.cpp"

// #define DEBUG

void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    initialize_glfw(SCR_WIDTH, SCR_HEIGHT);
    std::string title = "Hello OpenGL";
    GLFWwindow* window = create_glfw_window(SCR_WIDTH, SCR_HEIGHT, title);

    // std::vector<unsigned int> tringleShaderAndVAO = create_2_triangles();
    // std::vector<unsigned int> tringleShaderAndVAO = create_a_triangle();
    // std::vector<unsigned int> rectShaderAndVAO = create_a_rectangle();
    unsigned int vao = -1;
    Triangle triangles[] = {
        { 0.1f, 400, 300, 0, SCR_WIDTH, SCR_HEIGHT }, // center
        
        { 0.1f, 500, 400, 0, SCR_WIDTH, SCR_HEIGHT }, // top right
        { 0.1f, 600, 500, 0, SCR_WIDTH, SCR_HEIGHT }, // top right
        
        { 0.1f, 300, 400, 0, SCR_WIDTH, SCR_HEIGHT }, // top left
        { 0.1f, 200, 500, 0, SCR_WIDTH, SCR_HEIGHT }, // top left

        { 0.1f, 500, 200, 0, SCR_WIDTH, SCR_HEIGHT }, // bottom right
        { 0.1f, 600, 100, 0, SCR_WIDTH, SCR_HEIGHT }, // bottom right

        { 0.1f, 300, 200, 0, SCR_WIDTH, SCR_HEIGHT }, // bottom left
        { 0.1f, 200, 100, 0, SCR_WIDTH, SCR_HEIGHT }, // bottom left
    };

    for (int i = 0; i < (sizeof(triangles)/sizeof(Triangle)); i++)
    {
        triangles[i].initialize(vao);
    }

    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // rendering
        // first clear the screen
        render_clear_screen();
        // rest of the renders here
        // render_2_triangles(tringleShaderAndVAO[0], tringleShaderAndVAO[1]);
        // render_a_triangle(tringleShaderAndVAO[0], tringleShaderAndVAO[1]);
        // render_a_rectangle(rectShaderAndVAO[0], rectShaderAndVAO[1]);
        
        for (int i = 0; i < (sizeof(triangles)/sizeof(Triangle)); i++) triangles[i].render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
