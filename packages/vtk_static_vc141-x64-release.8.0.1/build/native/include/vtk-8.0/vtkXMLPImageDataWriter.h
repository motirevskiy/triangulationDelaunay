/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkXMLPImageDataWriter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkXMLPImageDataWriter
 * @brief   Write PVTK XML ImageData files.
 *
 * vtkXMLPImageDataWriter writes the PVTK XML ImageData file format.
 * One image data input can be written into a parallel file format
 * with any number of pieces spread across files.  The standard
 * extension for this writer's file format is "pvti".  This writer
 * uses vtkXMLImageDataWriter to write the individual piece files.
 *
 * @sa
 * vtkXMLImageDataWriter
*/

#ifndef vtkXMLPImageDataWriter_h
#define vtkXMLPImageDataWriter_h

#include "vtkIOParallelXMLModule.h" // For export macro
#include "vtkXMLPStructuredDataWriter.h"

class vtkImageData;

class VTKIOPARALLELXML_EXPORT vtkXMLPImageDataWriter : public vtkXMLPStructuredDataWriter
{
public:
  static vtkXMLPImageDataWriter* New();
  vtkTypeMacro(vtkXMLPImageDataWriter,vtkXMLPStructuredDataWriter);
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
  vtkXMLPImageDataWriter();
  ~vtkXMLPImageDataWriter() VTK_OVERRIDE;

  const char* GetDataSetName() VTK_OVERRIDE;
  void WritePrimaryElementAttributes(ostream &os, vtkIndent indent) VTK_OVERRIDE;
  vtkXMLStructuredDataWriter* CreateStructuredPieceWriter() VTK_OVERRIDE;

  // see algorithm for more info
  int FillInputPortInformation(int port, vtkInformation* info) VTK_OVERRIDE;

private:
  vtkXMLPImageDataWriter(const vtkXMLPImageDataWriter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkXMLPImageDataWriter&) VTK_DELETE_FUNCTION;
};

#endif
