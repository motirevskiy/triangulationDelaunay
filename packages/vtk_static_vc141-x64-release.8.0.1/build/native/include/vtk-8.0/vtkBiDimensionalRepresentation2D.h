/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkBiDimensionalRepresentation2D.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkBiDimensionalRepresentation2D
 * @brief   represent the vtkBiDimensionalWidget
 *
 * The vtkBiDimensionalRepresentation2D is used to represent the
 * bi-dimensional measure in a 2D (overlay) context. This representation
 * consists of two perpendicular lines defined by four
 * vtkHandleRepresentations. The four handles can be independently
 * manipulated consistent with the orthogonal constraint on the lines. (Note:
 * the four points are referred to as Point1, Point2, Point3 and
 * Point4. Point1 and Point2 define the first line; and Point3 and Point4
 * define the second orthogonal line.)
 *
 * To create this widget, you click to place the first two points. The third
 * point is mirrored with the fourth point; when you place the third point
 * (which is orthogonal to the lined defined by the first two points), the
 * fourth point is dropped as well. After definition, the four points can be
 * moved (in constrained fashion, preserving orthogonality). Further, the
 * entire widget can be translated by grabbing the center point of the widget;
 * each line can be moved along the other line; and the entire widget can be
 * rotated around its center point.
 *
 * @sa
 * vtkAngleWidget vtkHandleRepresentation vtkBiDimensionalRepresentation
*/

#ifndef vtkBiDimensionalRepresentation2D_h
#define vtkBiDimensionalRepresentation2D_h

#include "vtkInteractionWidgetsModule.h" // For export macro
#include "vtkBiDimensionalRepresentation.h"

class vtkHandleRepresentation;
class vtkCellArray;
class vtkPoints;
class vtkPolyData;
class vtkPolyDataMapper2D;
class vtkTextMapper;
class vtkActor2D;
class vtkProperty2D;
class vtkTextProperty;


class VTKINTERACTIONWIDGETS_EXPORT vtkBiDimensionalRepresentation2D : public vtkBiDimensionalRepresentation
{
public:
  /**
   * Instantiate the class.
   */
  static vtkBiDimensionalRepresentation2D *New();

  //@{
  /**
   * Standard VTK methods.
   */
  vtkTypeMacro(vtkBiDimensionalRepresentation2D,vtkBiDimensionalRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
  //@}

  //@{
  /**
   * Retrieve the property used to control the appearance of the two
   * orthogonal lines.
   */
  vtkGetObjectMacro(LineProperty,vtkProperty2D);
  vtkGetObjectMacro(SelectedLineProperty,vtkProperty2D);
  //@}

  //@{
  /**
   * Retrieve the property used to control the appearance of the text
   * labels.
   */
  vtkGetObjectMacro(TextProperty,vtkTextProperty);
  //@}

  // Used to communicate about the state of the representation
  enum {Outside=0,NearP1,NearP2,NearP3,NearP4,OnL1Inner,OnL1Outer,OnL2Inner,OnL2Outer,OnCenter};

  //@{
  /**
   * These are methods that satisfy vtkWidgetRepresentation's API.
   */
  void BuildRepresentation() VTK_OVERRIDE;
  int ComputeInteractionState(int X, int Y, int modify=0) VTK_OVERRIDE;
  void StartWidgetDefinition(double e[2]) VTK_OVERRIDE;
  void Point2WidgetInteraction(double e[2]) VTK_OVERRIDE;
  void Point3WidgetInteraction(double e[2]) VTK_OVERRIDE;
  void StartWidgetManipulation(double e[2]) VTK_OVERRIDE;
  void WidgetInteraction(double e[2]) VTK_OVERRIDE;
  void Highlight(int highlightOn) VTK_OVERRIDE;
  //@}

  //@{
  /**
   * Methods required by vtkProp superclass.
   */
  void ReleaseGraphicsResources(vtkWindow *w) VTK_OVERRIDE;
  int RenderOverlay(vtkViewport *viewport) VTK_OVERRIDE;
  //@}

  /**
   * Get the text shown in the widget's label.
   */
  char* GetLabelText() VTK_OVERRIDE;

  //@{
  /**
   * Get the position of the widget's label in display coordinates.
   */
  double* GetLabelPosition() VTK_OVERRIDE;
  void GetLabelPosition(double pos[3]) VTK_OVERRIDE;
  void GetWorldLabelPosition(double pos[3]) VTK_OVERRIDE;
  //@}

protected:
  vtkBiDimensionalRepresentation2D();
  ~vtkBiDimensionalRepresentation2D() VTK_OVERRIDE;

  // Geometry of the lines
  vtkCellArray        *LineCells;
  vtkPoints           *LinePoints;
  vtkPolyData         *LinePolyData;
  vtkPolyDataMapper2D *LineMapper;
  vtkActor2D          *LineActor;
  vtkProperty2D       *LineProperty;
  vtkProperty2D       *SelectedLineProperty;

  // The labels for the line lengths
  vtkTextProperty *TextProperty;
  vtkTextMapper   *TextMapper;
  vtkActor2D      *TextActor;

  // Helper method
  void ProjectOrthogonalPoint(double x[4], double y[3], double x1[3], double x2[3], double x21[3],
                              double dir, double xP[3]);

private:
  vtkBiDimensionalRepresentation2D(const vtkBiDimensionalRepresentation2D&) VTK_DELETE_FUNCTION;
  void operator=(const vtkBiDimensionalRepresentation2D&) VTK_DELETE_FUNCTION;
};

#endif
