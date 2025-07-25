#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <util/util.hpp>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


// Basic window rect that'll be where the screen renders to
float verts[] = {
	-1.0, -1.0, 0.0, 0.0,
	1.0, -1.0, 1.0, 0.0,
	1.0, 1.0, 1.0, 1.0,
	-1.0, 1.0, 0.0, 1.0
};


void Assert(unsigned char cond);
unsigned char ReadFile(const char *filePath, std::string *buff);
unsigned char CompileShader(GLuint *shader, std::string src);

void MouseCallback(GLFWwindow *window, double x, double y);




int main(int argc, char **argv) {
	
	// Init
	{ // These unamed sections deallocate because c++ allows you to make wierd higher level scopes like this
		unsigned char s = glfwInit();
		Assert((s != GLFW_FALSE));
	}
	
	// Open window with set dimensions and title
	int width = 800, height = 600;
	std::string title = "Window";
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	GLFWwindow *win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	Assert((win != nullptr));
	glfwMakeContextCurrent(win);
	
	// Create textures, vbos, vaos, & shaders
	{
		int s = (gladLoadGL() != false);
		if (s != true) {
			glfwDestroyWindow(win);
			glfwTerminate();
			exit(-1);
		}
	}
	GLuint vbo, vao, vs, fs, p;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);
	
	glBindVertexArray(vao);
	// Attribute index, number of elements per this attribute, attribute type, GL_FALSE, size of the amount of elements of specified type in bytes, (void *)0
	glVertexAttribPointer(0, 2, GL_FLOAT, false, (4 * sizeof(GL_FLOAT)), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, (4 * sizeof(GL_FLOAT)), (void *)(2 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	{ // Get & compile shaders
		std::string vss, fss;
		unsigned char s = ReadFile(".\\src\\vert.glsl", &vss);
		if (s != true) {
			std::cout << "Failed to read from file!" << std::endl;
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
			glfwDestroyWindow(win);
			glfwTerminate();
			exit(-1);
		}
		vs = glCreateShader(GL_VERTEX_SHADER);
		if (CompileShader(&vs, vss) != true) {
			std::cout << "Failed to compile!" << std::endl;
			glDeleteShader(vs);
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
			glfwDestroyWindow(win);
			glfwTerminate();
			exit(-1);
		}
		s = ReadFile(".\\src\\frag.glsl", &fss);
		if (s != true) {
			std::cout << "Failed to read from file!" << std::endl;
			glDeleteShader(vs);
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
			glfwDestroyWindow(win);
			glfwTerminate();
			exit(-1);
		}
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		if (CompileShader(&fs, fss) != true) {
			std::cout << "Failed to compile!" << std::endl;
			glDeleteShader(fs);
			glDeleteShader(vs);
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
			glfwDestroyWindow(win);
			glfwTerminate();
			exit(-1);
		}
		p = glCreateProgram();
		glAttachShader(p, vs);
		glAttachShader(p, fs);
		glLinkProgram(p); // Remember to check if linked propperly eventually
		glDeleteShader(fs);
		glDeleteShader(vs);
	}
	
	
	// Set up the texture & framebuffer
	// Framebuffer fbo;
	Texture2D tex(width, height, GL_RGBA32F);
	/*
	fbo.SetColorTexture(tex, GL_COLOR_ATTACHMENT0, 0);
	fbo.DSRDRRBUFF(width, height);
	if (fbo.CheckFBO() != true) {
		glDeleteProgram(p);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		glfwDestroyWindow(win);
		glfwTerminate();
		return -1;
	}
	*/
	
	
	// run loop it
	while (glfwWindowShouldClose(win) != true) {
		glfwPollEvents();
		
		double mx, my;
		glfwGetCursorPos(win, &mx, &my);
		
		glfwGetWindowSize(win, &width, &height);
		
		glBindVertexArray(vao);
		glUseProgram(p);
		glClear(GL_COLOR_BUFFER_BIT);
		// fbo.Bind();
		
		GLint tl = glGetUniformLocation(p, "txtr");
		glUniform1i(tl, 0); // Sets the texture slot of txtr to slot 0
		
		// Bind the texture to slot 0
		glActiveTexture(GL_TEXTURE0);
		glBindImageTexture(0, *tex.GetId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		
		glfwSwapBuffers(win);
		glBindVertexArray(0);
		glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		// tex.Unbind();
		// fbo.Unbind();
	}
	
	// clean & exit
	glDeleteProgram(p);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glfwDestroyWindow(win);
	glfwTerminate();
	
	return 0;
}


void Assert(unsigned char cond) {
	if (cond != true) {
		exit(-1);
	}
	return;
}

unsigned char ReadFile(const char *filePath, std::string *buff) {
	std::fstream f;
	std::string l;
	f.open(filePath);
	if (f.is_open() != true) {
		return false;
	}
	while (std::getline(f, l)) {
		l += '\n';
		*buff += l.c_str();
	}
	f.close();
	return true;
}

unsigned char CompileShader(GLuint *shader, std::string src) {
	const GLchar *s = (const GLchar *)src.c_str();
	glShaderSource(*shader, 1, &s, NULL);
	glCompileShader(*shader);
	GLint S = 0;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &S);
	if (S != GL_TRUE) {
		GLint ml = 0;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &ml);
		std::vector<GLchar> l(ml);
		glGetShaderInfoLog(*shader, ml, &ml, &l[0]);
		std::cout << &l[0] << std::endl;
		return false;
	}
	return true;
}





