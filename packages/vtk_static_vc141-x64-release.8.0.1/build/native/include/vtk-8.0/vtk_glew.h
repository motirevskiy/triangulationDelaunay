/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtk_glew.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtk_glew_h
#define vtk_glew_h

#define GLEW_NO_GLU

/* #undef VTK_BUILD_SHARED_LIBS */

#ifdef WIN32
#  ifndef VTK_BUILD_SHARED_LIBS
#    define GLEW_STATIC
#  endif
#endif


#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#define VTK_OPENGL_ES_VERSION 30

#ifdef ANDROID
#  include <GLES3/gl3.h>
#else
# if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#   include <OpenGLES/ES3/gl.h>
# else
/* Use the glew library configured for VTK.  */
/* #undef VTK_USE_SYSTEM_GLEW */
/* #undef VTK_USE_X */
#  ifdef VTK_USE_SYSTEM_GLEW
#    include <GL/glew.h>
#    ifdef WIN32
#      include <GL/wglew.h>
#    endif
//#    ifdef VTK_USE_X
//#      include <GL/glxew.h>
//#    endif
#  else
#    include <vtkglew/include/GL/glew.h>
#    ifdef WIN32
#      include <vtkglew/include/GL/wglew.h>
#    endif
//#    ifdef VTK_USE_X
//#      include <vtkglew/include/GL/glxew.h>
//#    endif
#  endif
# endif
#endif

/* some fixes for both ES 2 and 3 */
#if GL_ES_VERSION_3_0 == 1
#  define glDrawBuffer(arg)
#  define GL_BACK_LEFT 0
#  define GL_BACK_RIGHT 0
#  define GL_FRONT_LEFT 0
#  define GL_FRONT_RIGHT 0

/* this sends all the data each time as opposed to allowing a subset */
#  define glMultiDrawElements(mode, counts, type, indicies, primcount) \
      for (size_t eCount = 0; eCount < primcount; ++eCount) \
        { \
        glDrawElements(mode, *(counts + eCount), \
          type, (GLvoid *)(indicies[eCount])); \
        }

#endif

/*** deal with some GLES 3.0 specific issues ***/
#if GL_ES_VERSION_3_0 == 1
#  define GLEW_ARB_vertex_array_object 1
#  define GLEW_ARB_instanced_arrays 1
#endif

#endif
