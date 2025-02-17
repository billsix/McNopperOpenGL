/*
 * GLUS - Modern OpenGL, OpenGL ES and OpenVG Utilities. Copyright (C) since
 * 2010 Norbert Nopper
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "GL/glus.h"

GLUSboolean GLUSAPIENTRY glusProgramCreateFromSource(
    GLUSprogram *shaderProgram, const GLUSchar **vertexSource,
    const GLUSchar **fragmentSource) {
  GLUSint compiled;

  GLUSint logLength, charsWritten;

  char *log;

  if (!shaderProgram || !vertexSource || !fragmentSource) {
    return GLUS_FALSE;
  }

  shaderProgram->program = 0;
  shaderProgram->compute = 0;
  shaderProgram->vertex = 0;
  shaderProgram->fragment = 0;

  shaderProgram->vertex = glCreateShader(GLUS_VERTEX_SHADER);

  glShaderSource(shaderProgram->vertex, 1, (const char **)vertexSource, 0);

  glCompileShader(shaderProgram->vertex);

  glGetShaderiv(shaderProgram->vertex, GLUS_COMPILE_STATUS, &compiled);

  if (!compiled) {
    glGetShaderiv(shaderProgram->vertex, GLUS_INFO_LOG_LENGTH, &logLength);

    log = (char *)glusMemoryMalloc((size_t)logLength);

    if (!log) {
      return GLUS_FALSE;
    }

    glGetShaderInfoLog(shaderProgram->vertex, logLength, &charsWritten, log);

    glusLogPrint(GLUS_LOG_ERROR, "Vertex shader compile error:");
    glusLogPrint(GLUS_LOG_ERROR, "%s", log);

    glusMemoryFree(log);

    shaderProgram->vertex = 0;

    return GLUS_FALSE;
  }

  shaderProgram->fragment = glCreateShader(GLUS_FRAGMENT_SHADER);

  glShaderSource(shaderProgram->fragment, 1, (const char **)fragmentSource, 0);

  glCompileShader(shaderProgram->fragment);

  glGetShaderiv(shaderProgram->fragment, GLUS_COMPILE_STATUS, &compiled);

  if (!compiled) {
    glGetShaderiv(shaderProgram->fragment, GLUS_INFO_LOG_LENGTH, &logLength);

    log = (char *)glusMemoryMalloc((size_t)logLength);

    if (!log) {
      glusProgramDestroy(shaderProgram);

      return GLUS_FALSE;
    }

    glGetShaderInfoLog(shaderProgram->fragment, logLength, &charsWritten, log);

    glusLogPrint(GLUS_LOG_ERROR, "Fragment shader compile error:");
    glusLogPrint(GLUS_LOG_ERROR, "%s", log);

    glusMemoryFree(log);

    shaderProgram->fragment = 0;

    glusProgramDestroy(shaderProgram);

    return GLUS_FALSE;
  }

  shaderProgram->program = glCreateProgram();

  glAttachShader(shaderProgram->program, shaderProgram->vertex);

  glAttachShader(shaderProgram->program, shaderProgram->fragment);

  return GLUS_TRUE;
}

GLUSboolean GLUSAPIENTRY glusProgramCreateComputeFromSource(
    GLUSprogram *shaderProgram, const GLUSchar **computeSource) {
  GLUSint compiled;

  GLUSint logLength, charsWritten;

  char *log;

  if (!shaderProgram || !computeSource) {
    return GLUS_FALSE;
  }

  shaderProgram->program = 0;
  shaderProgram->compute = 0;
  shaderProgram->vertex = 0;
  shaderProgram->fragment = 0;

  shaderProgram->compute = glCreateShader(GLUS_COMPUTE_SHADER);

  glShaderSource(shaderProgram->compute, 1, (const char **)computeSource, 0);

  glCompileShader(shaderProgram->compute);

  glGetShaderiv(shaderProgram->compute, GLUS_COMPILE_STATUS, &compiled);

  if (!compiled) {
    glGetShaderiv(shaderProgram->compute, GLUS_INFO_LOG_LENGTH, &logLength);

    log = (char *)glusMemoryMalloc((size_t)logLength);

    if (!log) {
      return GLUS_FALSE;
    }

    glGetShaderInfoLog(shaderProgram->compute, logLength, &charsWritten, log);

    glusLogPrint(GLUS_LOG_ERROR, "Compute shader compile error:");
    glusLogPrint(GLUS_LOG_ERROR, "%s", log);

    glusMemoryFree(log);

    shaderProgram->compute = 0;

    return GLUS_FALSE;
  }

  shaderProgram->program = glCreateProgram();

  glAttachShader(shaderProgram->program, shaderProgram->compute);

  return GLUS_TRUE;
}

GLUSboolean GLUSAPIENTRY glusProgramLink(GLUSprogram *shaderProgram) {
  GLUSint linked;

  GLUSint logLength, charsWritten;

  char *log;

  if (!shaderProgram) {
    return GLUS_FALSE;
  }

  glLinkProgram(shaderProgram->program);

  glGetProgramiv(shaderProgram->program, GLUS_LINK_STATUS, &linked);

  if (!linked) {
    glGetProgramiv(shaderProgram->program, GLUS_INFO_LOG_LENGTH, &logLength);

    log = (char *)glusMemoryMalloc((size_t)logLength);

    if (!log) {
      glusProgramDestroy(shaderProgram);

      return GLUS_FALSE;
    }

    glGetProgramInfoLog(shaderProgram->program, logLength, &charsWritten, log);

    glusLogPrint(GLUS_LOG_ERROR, "Shader program link error:");
    glusLogPrint(GLUS_LOG_ERROR, "%s", log);

    glusMemoryFree(log);

    shaderProgram->program = 0;

    glusProgramDestroy(shaderProgram);

    return GLUS_FALSE;
  }

  return GLUS_TRUE;
}

GLUSboolean GLUSAPIENTRY glusProgramBuildFromSource(
    GLUSprogram *shaderProgram, const GLUSchar **vertexSource,
    const GLUSchar **fragmentSource) {
  if (!glusProgramCreateFromSource(shaderProgram, vertexSource,
                                   fragmentSource)) {
    return GLUS_FALSE;
  }

  return glusProgramLink(shaderProgram);
}

GLUSboolean GLUSAPIENTRY glusProgramBuildComputeFromSource(
    GLUSprogram *shaderProgram, const GLUSchar **computeSource) {
  if (!glusProgramCreateComputeFromSource(shaderProgram, computeSource)) {
    return GLUS_FALSE;
  }

  return glusProgramLink(shaderProgram);
}

GLUSboolean GLUSAPIENTRY glusProgramBuildSeparableFromSource(
    GLUSprogram *shaderProgram, const GLUSenum type, const GLUSchar **source) {
  GLUSint linked;

  GLUSint logLength, charsWritten;

  char *log;

  if (!shaderProgram || !source) {
    return GLUS_FALSE;
  }

  shaderProgram->program = 0;
  shaderProgram->compute = 0;
  shaderProgram->vertex = 0;
  shaderProgram->fragment = 0;

  shaderProgram->program =
      glCreateShaderProgramv(type, 1, (const char **)source);

  glGetProgramiv(shaderProgram->program, GLUS_LINK_STATUS, &linked);

  if (!linked) {
    glGetProgramiv(shaderProgram->program, GLUS_INFO_LOG_LENGTH, &logLength);

    log = (char *)glusMemoryMalloc((size_t)logLength);

    if (!log) {
      glusProgramDestroy(shaderProgram);

      return GLUS_FALSE;
    }

    glGetProgramInfoLog(shaderProgram->program, logLength, &charsWritten, log);

    glusLogPrint(GLUS_LOG_ERROR, "Shader program link error:");
    glusLogPrint(GLUS_LOG_ERROR, "%s", log);

    glusMemoryFree(log);

    shaderProgram->program = 0;

    glusProgramDestroy(shaderProgram);

    return GLUS_FALSE;
  }

  return GLUS_TRUE;
}

GLUSvoid GLUSAPIENTRY glusProgramDestroy(GLUSprogram *shaderprogram) {
  if (!shaderprogram) {
    return;
  }

  if (shaderprogram->program) {
    glDeleteProgram(shaderprogram->program);

    shaderprogram->program = 0;
  }

  if (shaderprogram->compute) {
    glDeleteShader(shaderprogram->compute);

    shaderprogram->compute = 0;
  }

  if (shaderprogram->fragment) {
    glDeleteShader(shaderprogram->fragment);

    shaderprogram->fragment = 0;
  }

  if (shaderprogram->vertex) {
    glDeleteShader(shaderprogram->vertex);

    shaderprogram->vertex = 0;
  }
}
