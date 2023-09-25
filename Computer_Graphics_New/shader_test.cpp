#include "pch.h"

GLint width, height;
GLuint ShaderID;

GLvoid drawScene();
GLvoid Reshape(int w, int h);

int main(int argc, char** argv)
{
	width = 500;
	height = 500;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example1");

	glewExperimental = GL_TRUE;
	glewInit();

	Shaders* shader = new Shaders();
	shader->makeVertexShaders();
	shader->makeFragmentShaders();
	ShaderID = shader->makeShaderProgram();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	glutMainLoop();

}

GLvoid drawScene()
{
	GLfloat rColor, gColor, bColor;
	
	rColor = gColor = 0.0f;
	bColor = 1.0f;
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(ShaderID);

	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 0, 1);

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}