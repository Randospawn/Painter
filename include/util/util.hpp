#ifndef __UTIL_HPP__
#define __UTIL_HPP__


#include "util.hpp"
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>




class Texture2D {
	private:
		GLuint id;
		unsigned char bound;
	public:
		Texture2D(int width = 800, int height = 600, GLenum format = GL_RGBA);
		void Bind(void);
		void Unbind(void);
		void Parameteri(GLenum parameter, GLint value);
		GLuint *GetId(void);
		~Texture2D(void);
};


class Framebuffer {
	private:
		GLuint id, rbid;
		unsigned char bound;
	public:
		Framebuffer(void);
		void Bind(void);
		void Unbind(void);
		void SetColorTexture(Texture2D texture, GLenum attachment, GLint mipMapLevel);
		void DSRDRRBUFF(int width, int height);
		unsigned char CheckFBO(void);
		~Framebuffer(void);
};







#endif




