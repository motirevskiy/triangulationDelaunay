/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPProjectSphereFilter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkPProjectSphereFilter
 * @brief   A filter to 'unroll' a sphere.  The
 * unroll longitude is -180.
 *
 *
*/

#ifndef vtkPProjectSphereFilter_h
#define vtkPProjectSphereFilter_h

#include "vtkFiltersParallelModule.h" // For export macro
#include "vtkProjectSphereFilter.h"

class VTKFILTERSPARALLEL_EXPORT vtkPProjectSphereFilter :
  public vtkProjectSphereFilter
{
public:
  vtkTypeMacro(vtkPProjectSphereFilter, vtkProjectSphereFilter);
  void PrintSelf(ostream &os, vtkIndent indent) VTK_OVERRIDE;

  static vtkPProjectSphereFilter *New();

protected:
  vtkPProjectSphereFilter();
  ~vtkPProjectSphereFilter() VTK_OVERRIDE;

  /**
   * Parallel part of the algorithm to figure out the closest point
   * to the centerline (i.e. line connecting -90 latitude to 90 latitude)
   * if we don't build cells using points at the poles.
   */
  void ComputePointsClosestToCenterLine(double, vtkIdList*) VTK_OVERRIDE;

  /**
   * If TranslateZ is true then this is the method that computes
   * the amount to translate.
   */
  double GetZTranslation(vtkPointSet* input) VTK_OVERRIDE;

private:
  vtkPProjectSphereFilter(const vtkPProjectSphereFilter &) VTK_DELETE_FUNCTION;
  void operator=(const vtkPProjectSphereFilter &) VTK_DELETE_FUNCTION;
};

#endif // vtkPProjectSphereFilter_h
