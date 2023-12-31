/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtk_libharu.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtk_libharu_h
#define vtk_libharu_h

#include "vtkConfigure.h"

/* Use the libharu library configured for VTK.  */
/* #undef VTK_USE_SYSTEM_LIBHARU */

#ifdef VTK_USE_SYSTEM_LIBHARU
/* Defined if using external libhary, and the library is a shared lib. */
/* #undef VTK_EXTERNAL_LIBHARU_IS_SHARED */
#endif

/* HPDF requires that HPDF_DLL be defined when linking against a shared library
 * on MSVC. */
#if defined(VTK_COMPILER_MSVC)

#ifdef VTK_USE_SYSTEM_LIBHARU

#ifdef VTK_EXTERNAL_LIBHARU_IS_SHARED
#define HPDF_DLL
#endif // VTK_EXTERNAL_LIBHARU_IS_SHARED

#elif defined(VTK_BUILD_SHARED_LIBS) // && !VTK_USE_SYSTEM_LIBHARU

#define HPDF_DLL

#endif // VTK_USE_SYSTEM_LIBHARU

#endif // VTK_COMPILER_MSVC

#ifdef VTK_USE_SYSTEM_LIBHARU
# include <hpdf.h>
#else
# include <vtklibharu/include/hpdf.h>
#endif

#endif // #ifndef vtk_libharu_h
