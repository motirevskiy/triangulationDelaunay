/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkXMLStructuredDataReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkXMLStructuredDataReader
 * @brief   Superclass for structured data XML readers.
 *
 * vtkXMLStructuredDataReader provides functionality common to all
 * structured data format readers.
 *
 * @sa
 * vtkXMLImageDataReader vtkXMLStructuredGridReader
 * vtkXMLRectilinearGridReader
*/

#ifndef vtkXMLStructuredDataReader_h
#define vtkXMLStructuredDataReader_h

#include "vtkIOXMLModule.h" // For export macro
#include "vtkXMLDataReader.h"


class VTKIOXML_EXPORT vtkXMLStructuredDataReader : public vtkXMLDataReader
{
public:
  vtkTypeMacro(vtkXMLStructuredDataReader,vtkXMLDataReader);
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

  /**
   * Get the number of points in the output.
   */
  vtkIdType GetNumberOfPoints() VTK_OVERRIDE;

  /**
   * Get the number of cells in the output.
   */
  vtkIdType GetNumberOfCells() VTK_OVERRIDE;

  //@{
  /**
   * Get/Set whether the reader gets a whole slice from disk when only
   * a rectangle inside it is needed.  This mode reads more data than
   * necessary, but prevents many short reads from interacting poorly
   * with the compression and encoding schemes.
   */
  vtkSetMacro(WholeSlices, int);
  vtkGetMacro(WholeSlices, int);
  vtkBooleanMacro(WholeSlices, int);
  //@}

  /**
   * For the specified port, copy the information this reader sets up in
   * SetupOutputInformation to outInfo
   */
  void CopyOutputInformation(vtkInformation *outInfo, int port) VTK_OVERRIDE;

protected:
  vtkXMLStructuredDataReader();
  ~vtkXMLStructuredDataReader() VTK_OVERRIDE;

  virtual void SetOutputExtent(int* extent)=0;
  int ReadPrimaryElement(vtkXMLDataElement* ePrimary) VTK_OVERRIDE;

  // Pipeline execute data driver.  Called by vtkXMLReader.
  void ReadXMLData() VTK_OVERRIDE;

  void SetupOutputInformation(vtkInformation *outInfo) VTK_OVERRIDE;

  // Internal representation of pieces in the file that may have come
  // from a streamed write.
  int* PieceExtents;
  int* PiecePointDimensions;
  vtkIdType* PiecePointIncrements;
  int* PieceCellDimensions;
  vtkIdType* PieceCellIncrements;

  // Whether to read in whole slices mode.
  int WholeSlices;

  // The update extent and corresponding increments and dimensions.
  int UpdateExtent[6];
  int PointDimensions[3];
  int CellDimensions[3];
  vtkIdType PointIncrements[3];
  vtkIdType CellIncrements[3];

  int WholeExtent[6];

  // The extent currently being read.
  int SubExtent[6];
  int SubPointDimensions[3];
  int SubCellDimensions[3];

  // Override methods from superclass.
  void SetupEmptyOutput() VTK_OVERRIDE;
  void SetupPieces(int numPieces) VTK_OVERRIDE;
  void DestroyPieces() VTK_OVERRIDE;
  int ReadArrayForPoints(vtkXMLDataElement* da,
    vtkAbstractArray* outArray) VTK_OVERRIDE;
  int ReadArrayForCells(vtkXMLDataElement* da,
    vtkAbstractArray* outArray) VTK_OVERRIDE;

  // Internal utility methods.
  int ReadPiece(vtkXMLDataElement* ePiece) VTK_OVERRIDE;
  virtual int ReadSubExtent(
    int* inExtent, int* inDimensions, vtkIdType* inIncrements,
    int* outExtent,int* outDimensions,vtkIdType* outIncrements,
    int* subExtent, int* subDimensions, vtkXMLDataElement* da,
    vtkAbstractArray* array, FieldType type);

private:
  vtkXMLStructuredDataReader(const vtkXMLStructuredDataReader&) VTK_DELETE_FUNCTION;
  void operator=(const vtkXMLStructuredDataReader&) VTK_DELETE_FUNCTION;
};

#endif
