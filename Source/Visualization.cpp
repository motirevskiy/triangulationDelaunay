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

Visualization::Visualization()
{
}

Visualization::~Visualization()
{
}

void Visualization::visualize(vector<Vector3D*>& dots, vector<tuple<int, int, int>*>& mesh)
{
    vtkUnsignedCharArray* clr = vtkUnsignedCharArray::New();
    vtkPoints* pts = vtkPoints::New();
    vtkCellArray* clArr = vtkCellArray::New();

    clr->SetName("Colors");
    clr->SetNumberOfComponents(3);

    vector<Vector3D*>::iterator dotIt;
    for (dotIt = dots.begin(); dotIt != dots.end(); dotIt++)
    {
        Vector3D* d = *dotIt;
        pts->InsertNextPoint(d->X, d->Y, d->Z);
        clr->InsertNextTuple3(255, 248, 220);
    }

    vtkTriangle* vtkTri;
    vector<tuple<int, int, int>*>::iterator meshIt;
    for (meshIt = mesh.begin(); meshIt != mesh.end(); meshIt++)
    {
        vtkTri = vtkTriangle::New();
        vtkTri->GetPointIds()->SetId(0, get<0>(**meshIt));
        vtkTri->GetPointIds()->SetId(1, get<1>(**meshIt));
        vtkTri->GetPointIds()->SetId(2, get<2>(**meshIt));

        clArr->InsertNextCell(vtkTri);
    }

    vtkRenderer* rndr = vtkRenderer::New();
    vtkRenderWindow* wndw = vtkRenderWindow::New();
    wndw->AddRenderer(rndr);

    vtkRenderWindowInteractor* rwi =
        vtkRenderWindowInteractor::New();
    rwi->SetRenderWindow(wndw);

    vtkInteractorStyleTrackballCamera* style =
        vtkInteractorStyleTrackballCamera::New();
    rwi->SetInteractorStyle(style);

    vtkPolyData* polyData = vtkPolyData::New();

    polyData->SetPoints(pts);
    polyData->SetPolys(clArr);
    polyData->GetPointData()->SetScalars(clr);

    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInputData(polyData);

    vtkActor* actr = vtkActor::New();
    actr->SetMapper(mapper);

    rndr->AddActor(actr);

    rndr->SetBackground(0.1, 0.2, 0.4);
    wndw->SetSize(1280, 960);

    wndw->Render();

    vtkWindowToImageFilter* w2if = vtkWindowToImageFilter::New();
    w2if->SetInput(wndw);

    w2if->Update();
    vtkImageData* imgData = w2if->GetOutput();

    vtkPNGWriter* pngWriter = vtkPNGWriter::New();
    pngWriter->SetFileName("output.png");
    pngWriter->SetInputData(imgData);
    pngWriter->Write();

    rwi->Start();

    pts->Delete();
    clr->Delete();
    clArr->Delete();
    rndr->Delete();
    wndw->Delete();
    rwi->Delete();
    style->Delete();
    polyData->Delete();
    mapper->Delete();
    actr->Delete();
    w2if->Delete();
    imgData->Delete();
    pngWriter->Delete();
}

#endif