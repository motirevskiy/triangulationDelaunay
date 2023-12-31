/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkScalarBarRepresentation.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/*
 * Copyright 2008 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */

/**
 * @class   vtkScalarBarRepresentation
 * @brief   represent scalar bar for vtkScalarBarWidget
 *
 *
 *
 * This class represents a scalar bar for a vtkScalarBarWidget.  This class
 * provides support for interactively placing a scalar bar on the 2D overlay
 * plane.  The scalar bar is defined by an instance of vtkScalarBarActor.
 *
 * One specialty of this class is that if the scalar bar is moved near enough
 * to an edge, it's orientation is flipped to match that edge.
 *
 * @sa
 * vtkScalarBarWidget vtkWidgetRepresentation vtkScalarBarActor
 *
*/

#ifndef vtkScalarBarRepresentation_h
#define vtkScalarBarRepresentation_h

#include "vtkInteractionWidgetsModule.h" // For export macro
#include "vtkBorderRepresentation.h"

class vtkScalarBarActor;

class VTKINTERACTIONWIDGETS_EXPORT vtkScalarBarRepresentation : public vtkBorderRepresentation
{
public:
  vtkTypeMacro(vtkScalarBarRepresentation, vtkBorderRepresentation);
  void PrintSelf(ostream &os, vtkIndent indent) VTK_OVERRIDE;
  static vtkScalarBarRepresentation *New();

  //@{
  /**
   * The prop that is placed in the renderer.
   */
  vtkGetObjectMacro(ScalarBarActor, vtkScalarBarActor);
  virtual void SetScalarBarActor(vtkScalarBarActor *);
  //@}

  //@{
  /**
   * Satisfy the superclass' API.
   */
  void BuildRepresentation() VTK_OVERRIDE;
  void WidgetInteraction(double eventPos[2]) VTK_OVERRIDE;
  void GetSize(double size[2]) VTK_OVERRIDE
    {size[0]=2.0; size[1]=2.0;}
  //@}

  //@{
  /**
   * These methods are necessary to make this representation behave as
   * a vtkProp.
   */
  int GetVisibility() VTK_OVERRIDE;
  void SetVisibility(int) VTK_OVERRIDE;
  void GetActors2D(vtkPropCollection *collection) VTK_OVERRIDE;
  void ReleaseGraphicsResources(vtkWindow *window) VTK_OVERRIDE;
  int RenderOverlay(vtkViewport*) VTK_OVERRIDE;
  int RenderOpaqueGeometry(vtkViewport*) VTK_OVERRIDE;
  int RenderTranslucentPolygonalGeometry(vtkViewport*) VTK_OVERRIDE;
  int HasTranslucentPolygonalGeometry() VTK_OVERRIDE;
  //@}

  //@{
  /**
   * If true, the orientation will be updated based on the widget's position.
   * Default is true.
   */
  vtkSetMacro(AutoOrient, bool)
  vtkGetMacro(AutoOrient, bool)
  //@}

  //@{
  /**
   * Get/Set the orientation.
   */
  void SetOrientation(int orient);
  int GetOrientation();
  //@}

protected:
  vtkScalarBarRepresentation();
  ~vtkScalarBarRepresentation() VTK_OVERRIDE;

  /**
   * Change horizontal <--> vertical orientation, rotate the corners of the
   * bar to preserve size, and swap the resize handle locations.
   */
  void SwapOrientation();

  vtkScalarBarActor *ScalarBarActor;
  bool AutoOrient;

private:
  vtkScalarBarRepresentation(const vtkScalarBarRepresentation &) VTK_DELETE_FUNCTION;
  void operator=(const vtkScalarBarRepresentation &) VTK_DELETE_FUNCTION;
};

#endif //vtkScalarBarRepresentation_h
