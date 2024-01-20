#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void render_clear_screen()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}