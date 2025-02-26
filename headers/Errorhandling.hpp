#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GL/gl.h>

#define GL_CHECK(stmt) do { \
    stmt; \
    checkOpenGLError(#stmt, __FILE__, __LINE__); \
} while (0)

inline void checkOpenGLError(const char* stmt, const char* fname, int line) {
    GLenum err = glGetError();
    while (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error " << err << " in " << stmt << " at " << fname << ":" << line << std::endl;
        err = glGetError();
    }
}