//
// Created by steel99xl on 3/25/22.
//

#ifndef KAIJUGL_KAIJURENDERWARNINGS_HPP
#define KAIJUGL_KAIJURENDERWARNINGS_HPP
#include <GL/glew.h>
#include <iostream>
#include <functional>

#define GLCall(function); GLClearError(); function; GLLogCall(#function, __FILE__, __LINE__);
void GLClearError();

void GLLogCall(const char *function, const char *file, int line);

#endif //KAIJUGL_KAIJURENDERWARNINGS_HPP
