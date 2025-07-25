#include "util.hpp"
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>




Framebuffer::Framebuffer(void) {
	glGenFramebuffers(1, &this->id);
	return;
}
void Framebuffer::Bind(void) {
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	this->bound = true;
	return;
}
void Framebuffer::Unbind(void) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->bound = false;
	return;
}
void Framebuffer::SetColorTexture(Texture2D texture, GLenum attachment, GLint mipMapLevel) {
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, *texture.GetId(), mipMapLevel);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return;
}
void Framebuffer::DSRDRRBUFF(int width, int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	GLuint depthStencilRBO;
	glGenRenderbuffers(1, &depthStencilRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRBO);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return;
}
unsigned char Framebuffer::CheckFBO(void) {
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}
Framebuffer::~Framebuffer(void) {
	if (this->bound) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		this->bound = false;
	}
	glDeleteFramebuffers(1, &this->id);
	return;
}


Texture2D::Texture2D(int width, int height, GLenum format) {
	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);
	// Set to defaults (of my version)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Allocate the image
	/*
		"Target": is always "GL_TEXTURE_2D" for this kind of 2d texture.
		
		"Level": is the level of detail (0 is default lod).
		
		"Internal Format": is the color format of this textures data.
		
		"Width & Height": bruh (if you don't know stop doing graphics programming).
		
		"Border": also mostly self explanitory, but just for later it's the border
		width (0 is no border).
		
		"Format" & "type": specify the data type & format of the color components of
		images given as input to the texture.
		
		"Pixels": self explanitory + (whatevs bruh, it's the freakin input image dude
		((((void *)0 means it'll allocate an entirely new image)))).
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (void *)0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return;
}
void Texture2D::Bind(void) {
	glBindTexture(GL_TEXTURE_2D, this->id);
	this->bound = true;
	return;
}
void Texture2D::Unbind(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
	this->bound = false;
	return;
}
void Texture2D::Parameteri(GLenum parameter, GLint value) {
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexParameteri(GL_TEXTURE_2D, parameter, value);
	glBindTexture(GL_TEXTURE_2D, 0);
	return;
}
GLuint *Texture2D::GetId(void) {
	return &this->id;
}
Texture2D::~Texture2D(void) { // Deallocates the actual texture data with only that btw
	if (this->bound) {
		glBindTexture(GL_TEXTURE_2D, 0);
		this->bound = false;
	}
	glDeleteTextures(1, &this->id);
	return;
}










