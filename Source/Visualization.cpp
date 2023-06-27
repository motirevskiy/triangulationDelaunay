#define VISUAL
#ifdef VISUAL
#include <tuple>
#include <vector>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include "../Header/Visualization.h"
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

using namespace std;
using namespace dt;

Visualization::Visualization(bool isShowWireframe)
{
    IsShowWireframe = isShowWireframe;
}

Visualization::~Visualization()
{
}

void Visualization::ReconstructIn3D(vector<Vector3D*>& dots, vector<tuple<int, int, int>*>& mesh)
{
    vtkPoints* points = vtkPoints::New();
    vtkUnsignedCharArray* colors = vtkUnsignedCharArray::New();
    vtkCellArray* cells = vtkCellArray::New();

    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");

    vector<Vector3D*>::iterator itDots;
    for (itDots = dots.begin(); itDots != dots.end(); itDots++)
    {
        Vector3D* dot = *itDots;
        points->InsertNextPoint(dot->X, dot->Y, dot->Z);
        colors->InsertNextTuple3(255, 248, 220);
    }

    vtkTriangle* vtkTriangle;
    vector<tuple<int, int, int>*>::iterator itMesh;
    for (itMesh = mesh.begin(); itMesh != mesh.end(); itMesh++)
    {
        vtkTriangle = vtkTriangle::New();
        vtkTriangle->GetPointIds()->SetId(0, get<0>(**itMesh));
        vtkTriangle->GetPointIds()->SetId(1, get<1>(**itMesh));
        vtkTriangle->GetPointIds()->SetId(2, get<2>(**itMesh));

        cells->InsertNextCell(vtkTriangle);
    }

    vtkRenderer* renderer = vtkRenderer::New();
    vtkRenderWindow* renderWindow = vtkRenderWindow::New();
    renderWindow->AddRenderer(renderer);

    vtkRenderWindowInteractor* renderWindowInteractor =
        vtkRenderWindowInteractor::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkInteractorStyleTrackballCamera* style =
        vtkInteractorStyleTrackballCamera::New();
    renderWindowInteractor->SetInteractorStyle(style);

    vtkPolyData* trianglePolyData = vtkPolyData::New();

    trianglePolyData->SetPoints(points);
    trianglePolyData->SetPolys(cells);
    trianglePolyData->GetPointData()->SetScalars(colors);

    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInputData(trianglePolyData);

    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);

    renderer->SetBackground(0.1, 0.2, 0.4);
    renderWindow->SetSize(1280, 960);

    renderWindow->Render();

    vtkWindowToImageFilter* windowToImageFilter = vtkWindowToImageFilter::New();
    windowToImageFilter->SetInput(renderWindow);

    windowToImageFilter->Update();
    vtkImageData* imageData = windowToImageFilter->GetOutput();

    vtkPNGWriter* writer = vtkPNGWriter::New();
    writer->SetFileName("output.png");
    writer->SetInputData(imageData);
    writer->Write();

    renderWindowInteractor->Start();

    points->Delete();
    colors->Delete();
    cells->Delete();
    renderer->Delete();
    renderWindow->Delete();
    renderWindowInteractor->Delete();
    style->Delete();
    trianglePolyData->Delete();
    mapper->Delete();
    actor->Delete();
    windowToImageFilter->Delete();
    imageData->Delete();
    writer->Delete();
}




#endif