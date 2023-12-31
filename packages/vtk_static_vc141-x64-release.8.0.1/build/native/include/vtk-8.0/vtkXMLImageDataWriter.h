/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkXMLImageDataWriter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkXMLImageDataWriter
 * @brief   Write VTK XML ImageData files.
 *
 * vtkXMLImageDataWriter writes the VTK XML ImageData file format.
 * One image data input can be written into one file in any number of
 * streamed pieces.  The standard extension for this writer's file
 * format is "vti".  This writer is also used to write a single piece
 * of the parallel file format.
 *
 * @sa
 * vtkXMLPImageDataWriter
*/

#ifndef vtkXMLImageDataWriter_h
#define vtkXMLImageDataWriter_h

#include "vtkIOXMLModule.h" // For export macro
#include "vtkXMLStructuredDataWriter.h"

class vtkImageData;

class VTKIOXML_EXPORT vtkXMLImageDataWriter : public vtkXMLStructuredDataWriter
{
public:
  static vtkXMLImageDataWriter* New();
  vtkTypeMacro(vtkXMLImageDataWriter,vtkXMLStructuredDataWriter);
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

  /**
   * Get/Set the writer's input.
   */
  vtkImageData* GetInput();

  /**
   * Get the default file extension for files written by this writer.
   */
  const char* GetDefaultFileExtension() VTK_OVERRIDE;

protected:
  vtkXMLImageDataWriter();
  ~vtkXMLImageDataWriter() VTK_OVERRIDE;

  // see algorithm for more info
  int FillInputPortInformation(int port, vtkInformation* info) VTK_OVERRIDE;

  void WritePrimaryElementAttributes(ostream &os, vtkIndent indent) VTK_OVERRIDE;
  void GetInputExtent(int* extent) VTK_OVERRIDE;
  const char* GetDataSetName() VTK_OVERRIDE;

private:
  vtkXMLImageDataWriter(const vtkXMLImageDataWriter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkXMLImageDataWriter&) VTK_DELETE_FUNCTION;
};

#endif
