#include "Particle.h"
#include "ogl/oglGeometry.h"
#include "ogl/loadTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>
#include <FreeImage.h>

// Number of particles is PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH
const int PARTICLE_TEXTURE_WIDTH  = 16;

namespace byhj
{

Particle::Particle()
{

}

Particle::~Particle()
{

}

void Particle::Init()
{

	init_buffer();
	init_vertexArray();
	init_shader();
	init_texture();
}

void Particle::Render(float aspect)
{
	//Use this shader and vao data to render
	glUseProgram(program);
	glBindVertexArray(vao);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	float currentTime = static_cast<float>( glfwGetTime());
	glm::mat4 view  = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj  = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniform.model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(uniform.view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(uniform.proj_loc, 1, GL_FALSE, &proj[0][0]);

	// Variable for switching between the buffers.
	static GLint flip = 0;

	//
	// Update the particle point data.
	//

	glUseProgram(g_programUpdatePoints.program);

	glUniform1f(g_timeLocation, time);

	// Bind to the writing buffer.
	glBindFramebuffer(GL_FRAMEBUFFER, g_positionFramebuffer[(flip + 1) % 2]);

	// Set the viewport to the texture size.
	glViewport(0, 0, PARTICLE_TEXTURE_WIDTH, PARTICLE_TEXTURE_WIDTH);

	// This texture contains the current particle data.
	glBindTexture(GL_TEXTURE_2D, g_positionTexture[flip]);

	glBindVertexArray(g_vaoUpdatePoints);

	// Draw all particles, data is updated in the shader.
	glDrawArrays(GL_POINTS, 0, PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH);

	// Go back to the window buffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Reset the viewport.
	glViewport(0, 0, g_widthViewport, g_heightViewport);

	//
	// Draw the particles on the screen.
	//

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glBindVertexArray(vao);

	// Use the particle data from current frame. Updated data is used in next frame.
	glBindTexture(GL_TEXTURE_2D, g_positionTexture[flip]);

	// Draw point sprites by blending them.
	glEnable(GL_BLEND);
	glDrawArrays(GL_POINTS, 0, PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH);
	glDisable(GL_BLEND);

	// Switch to the next buffer.
	flip = (flip + 1) % 2;

	glBindVertexArray(0);
	glUseProgram(0);
}


void Particle::Shutdown()
{
	glDeleteProgram(program);
}


void Particle::init_buffer()
{

	// Points for accessing the texel, which contain the particle data.
	GLfloat points[PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH * 2];
	// Array containing the initial particles.
	GLfloat particle[PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH * 4];

	for (int y = 0; y < PARTICLE_TEXTURE_WIDTH; y++)
	{
		for (int x = 0; x < PARTICLE_TEXTURE_WIDTH; x++)
		{
			points[x * 2 + 0 + y * PARTICLE_TEXTURE_WIDTH * 2] = (GLfloat)x / (GLfloat)PARTICLE_TEXTURE_WIDTH;
			points[x * 2 + 1 + y * PARTICLE_TEXTURE_WIDTH * 2] = (GLfloat)y / (GLfloat)PARTICLE_TEXTURE_WIDTH;
		}
	}

	for (int y = 0; y < PARTICLE_TEXTURE_WIDTH; y++)
	{
		for (int x = 0; x < PARTICLE_TEXTURE_WIDTH; x++)
		{
			particle[x * 4 + 0 + y * PARTICLE_TEXTURE_WIDTH * 4] = 0.0f;
			particle[x * 4 + 1 + y * PARTICLE_TEXTURE_WIDTH * 4] = 0.0f;
			particle[x * 4 + 2 + y * PARTICLE_TEXTURE_WIDTH * 4] = 0.0f;
			particle[x * 4 + 3 + y * PARTICLE_TEXTURE_WIDTH * 4] = -1.0f; // w < 0.0 means a dead particle. So renewed in first frame.
		}
	}

	glGenTextures(2, posTextures);

	glBindTexture(GL_TEXTURE_2D, posTextures[0]);
	// Create a texture containing floats.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, PARTICLE_TEXTURE_WIDTH, PARTICLE_TEXTURE_WIDTH, 0, GL_RGBA, GL_FLOAT, particle);

	// Important: No interpolation.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glBindTexture(GL_TEXTURE_2D, posTextures[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, PARTICLE_TEXTURE_WIDTH, PARTICLE_TEXTURE_WIDTH, 0, GL_RGBA, GL_FLOAT, particle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(2, posFbos);

	// Attach the texture.
	glBindFramebuffer(GL_FRAMEBUFFER, posFbos[0]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posTextures[0], 0);

	glBindFramebuffer(GL_FRAMEBUFFER, posFbos[1]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posTextures[1], 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_TEXTURE_WIDTH * PARTICLE_TEXTURE_WIDTH * 2 * sizeof(GLfloat), (GLfloat*)points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Particle::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,  2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void Particle::init_shader()
{
	ParticleShader.init();
	ParticleShader.attach(GL_VERTEX_SHADER, "Particle.vert");
	ParticleShader.attach(GL_FRAGMENT_SHADER, "Particle.frag");
	ParticleShader.link();
	program = ParticleShader.GetProgram();

	uniform.model_loc = glGetUniformLocation(program, "model");
	uniform.view_loc = glGetUniformLocation(program, "view");
	uniform.proj_loc = glGetUniformLocation(program, "proj");
}



void Particle::init_texture()
{
	particleTex = loadTexture("../../media/textures/Particle.tag");
}

}