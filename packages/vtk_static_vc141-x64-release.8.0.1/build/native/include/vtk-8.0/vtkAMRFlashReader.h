/*=========================================================================

 Program:   Visualization Toolkit
 Module:    vtkAMRFlashReader.h

 Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 All rights reserved.
 See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

 =========================================================================*/
/**
 * @class   vtkAMREnzoReader
 *
 *
 * A concrete instance of vtkAMRBaseReader that implements functionality
 * for reading Flash AMR datasets.
*/

#ifndef vtkAMRFlashReader_h
#define vtkAMRFlashReader_h

#include "vtkIOAMRModule.h" // For export macro
#include "vtkAMRBaseReader.h"

class vtkOverlappingAMR;
class vtkFlashReaderInternal;

class VTKIOAMR_EXPORT vtkAMRFlashReader : public vtkAMRBaseReader
{
public:
  static vtkAMRFlashReader* New();
  vtkTypeMacro( vtkAMRFlashReader, vtkAMRBaseReader );
  void PrintSelf(ostream &os, vtkIndent indent ) VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::GetNumberOfBlocks
   */
  int GetNumberOfBlocks() VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::GetNumberOfLevels
   */
  int GetNumberOfLevels() VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::SetFileName
   */
  void SetFileName( const char* fileName ) VTK_OVERRIDE;

protected:
  vtkAMRFlashReader();
  ~vtkAMRFlashReader() VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::ReadMetaData
   */
  void ReadMetaData() VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::GetBlockLevel
   */
  int GetBlockLevel( const int blockIdx ) VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::FillMetaData
   */
  int FillMetaData( ) VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::GetAMRGrid
   */
  vtkUniformGrid* GetAMRGrid( const int blockIdx ) VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::GetAMRGridData
   */
  void GetAMRGridData(
      const int blockIdx, vtkUniformGrid *block, const char *field) VTK_OVERRIDE;

  /**
   * See vtkAMRBaseReader::GetAMRGridData
   */
  void GetAMRGridPointData(
      const int vtkNotUsed(blockIdx), vtkUniformGrid *vtkNotUsed(block), const char *vtkNotUsed(field)) VTK_OVERRIDE {;}

  /**
   * See vtkAMRBaseReader::SetUpDataArraySelections
   */
  void SetUpDataArraySelections() VTK_OVERRIDE;

  bool IsReady;

private:
  vtkAMRFlashReader( const vtkAMRFlashReader& ) VTK_DELETE_FUNCTION;
  void operator=(const vtkAMRFlashReader& ) VTK_DELETE_FUNCTION;

  void ComputeStats(vtkFlashReaderInternal* internal, std::vector<int>& numBlocks, double min[3]);
  vtkFlashReaderInternal *Internal;
};

#endif /* vtkAMRFlashReader_h */
