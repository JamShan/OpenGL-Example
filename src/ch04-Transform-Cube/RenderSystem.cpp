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
	windowInfo.title += "Cube";
}

void RenderSystem::v_Init()
{
	//glEnable(GL_DEPTH_TEST);

	m_Triangle.Init();
}

void RenderSystem::v_Render()
{

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &one);

	static const float aspect = GetAspect();
	m_Triangle.Render(aspect);

}

void RenderSystem::v_Shutdown()
{
	m_Triangle.Shutdown();
}
}