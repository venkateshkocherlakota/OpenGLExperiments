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
    Triangle triangle = { 0.1f, 400, 300, 0, SCR_WIDTH, SCR_HEIGHT };
    triangle.initialize();
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
        triangle.render();
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
