#include <GL/glew.h>
#include "RenderSystem.h"

namespace byhj
{

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::v_InitInfo()
{
	windowInfo.title += "ch01-Window";
}

void RenderSystem::v_Init()
{
	m_Window.Init();
}

void RenderSystem::v_Render()
{

	const GLfloat bgColor[] = {	0.2f, 0.3f, 0.5f, 1.0f};
	glClearBufferfv(GL_COLOR, 0, bgColor);

	m_Window.Render();

}

void RenderSystem::v_Shutdown()
{
	m_Window.Shutdown();
}
}