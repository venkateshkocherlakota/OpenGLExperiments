#pragma once

#include <limits.h>

class Triangle {
    // declare gl handles
    unsigned int vao, vbo, shaderProgram;
    // triangle vertices
    // float vertices[9] = {
    //     -1.0f, -1.0f, 0.0f,
    //     1.0f, -1.0f, 0.0f,
    //     0.0f, 1.0f, 0.0f
    // }; 
    float vertices[18] = {
        // positions         // colors
        -1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
         1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

    };
    public:
        float sizeFactor;
        int x, y ,z;
        unsigned int screenWidth, screenHeight;

        Triangle(float scale, int X, int Y, int Z, unsigned int scrWidth, unsigned int scrHeight)
        {
            sizeFactor = scale;
            x = X;
            y = Y;
            z = Z;
            screenWidth = scrWidth;
            screenHeight = scrHeight;
        }

        void initialize(unsigned int& VAO)
        {
            // build vertex shader
            unsigned int vertexShader = generate_vertex_shader();
            // build fragment shader
            unsigned int fragShader = generate_frag_shader();
            // link shaders
            shaderProgram = generate_program_shader(vertexShader, fragShader);
            // define the vertices to be rendered
            calculateVertices();
            if (VAO == -1)
            {
                glGenVertexArrays(1, &vao);
            } else {
                vao = VAO;
            }
            glGenBuffers(1, &vbo);
            // bind the Vertex Array Object first, 
            // then bind and set vertex buffer(s), 
            // and then configure vertex attributes(s).
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0); 

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);
        }

        void render()
        {
            // draw our first triangle
            glUseProgram(shaderProgram);
            glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0); // no need to unbind it every time 
        }
    
    private:
        void calculateVertices() {
            // scale based on given size factor
            // for (int i = 0; i < 18; i++) vertices[i] *= sizeFactor;
            // normalize location value
            float offsetX = mapFloat(x, 0, -1.0f, screenWidth, 1.0f);
            float offsetY = mapFloat(y, 0, -1.0f, screenHeight, 1.0f);
            // offset X coordinates
            vertices[0] = (vertices[0] * sizeFactor) + offsetX;
            vertices[6] = (vertices[6] * sizeFactor) + offsetX;
            vertices[12] = (vertices[12] * sizeFactor) + offsetX;
            // offset Y coordinates
            vertices[1] = (vertices[1] * sizeFactor) + offsetY;
            vertices[7] = (vertices[7] * sizeFactor) + offsetY;
            vertices[13] = (vertices[13] * sizeFactor) + offsetY;

            #if DEBUG
            std::cout << "Loc X: " << offsetX << " loc Y: " << offsetY << "\n Vertices:\n";
            for(int i=0; i<9; i++)
            {
                std::cout << vertices[i] << " ";
            }
            std::cout << std::endl;
            #endif
        }

        float mapFloat(
            float input_value, float input_range_start, float output_range_start,
            float input_range_end, float output_range_end
        )
        {
            return (input_value - input_range_start) * (output_range_end - output_range_start)
                     / (input_range_end - input_range_start) + output_range_start;
        }
};