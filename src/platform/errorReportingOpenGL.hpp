// This file is copied from https://github.com/meemknight/ourCraft/blob/master/include/gameLayer/errorReporting.h
#pragma once
#include <glad/glad.h>


//https://learnopengl.com/In-Practice/Debugging
void GLAPIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

void enableReportGlErrors();

void createErrorFile();

void reportError(const char *message);