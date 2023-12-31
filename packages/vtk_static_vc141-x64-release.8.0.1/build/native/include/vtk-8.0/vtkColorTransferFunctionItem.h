/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkColorTransferFunctionItem.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef vtkColorTransferFunctionItem_h
#define vtkColorTransferFunctionItem_h

#include "vtkChartsCoreModule.h" // For export macro
#include "vtkScalarsToColorsItem.h"

class vtkColorTransferFunction;
class vtkImageData;

// Description:
// vtkPlot::Color, vtkPlot::Brush, vtkScalarsToColors::DrawPolyLine,
// vtkScalarsToColors::MaskAboveCurve have no effect here.
class VTKCHARTSCORE_EXPORT vtkColorTransferFunctionItem: public vtkScalarsToColorsItem
{
public:
  static vtkColorTransferFunctionItem* New();
  vtkTypeMacro(vtkColorTransferFunctionItem, vtkScalarsToColorsItem);
  void PrintSelf(ostream &os, vtkIndent indent) VTK_OVERRIDE;

  void SetColorTransferFunction(vtkColorTransferFunction* t);
  vtkGetObjectMacro(ColorTransferFunction, vtkColorTransferFunction);

protected:
  vtkColorTransferFunctionItem();
  ~vtkColorTransferFunctionItem() VTK_OVERRIDE;

  // Description:
  // Returns true if we are rendering in log space.
  virtual bool UsingLogScale();


  // Description:
  // Reimplemented to return the range of the lookup table
  void ComputeBounds(double bounds[4]) VTK_OVERRIDE;

  void ComputeTexture() VTK_OVERRIDE;
  vtkColorTransferFunction* ColorTransferFunction;
private:
  vtkColorTransferFunctionItem(const vtkColorTransferFunctionItem&) VTK_DELETE_FUNCTION;
  void operator=(const vtkColorTransferFunctionItem&) VTK_DELETE_FUNCTION;
};

#endif
