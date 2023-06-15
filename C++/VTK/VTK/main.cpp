#include<stdio.h>

#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);

#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>

void main() {

	vtkConeSource* cone = vtkConeSource::New(); //3D 객체
	cone->SetHeight(3.0);
	cone->SetRadius(1.0);
	cone->SetResolution(50);

	vtkPolyDataMapper* coneMapper = vtkPolyDataMapper::New(); //Mapper
	coneMapper->SetInputConnection(cone->GetOutputPort());

	vtkProperty* property = vtkProperty::New(); //속성
	property->SetColor(1.0, 0.3882, 0.2784);
	property->SetDiffuse(0.7);
	property->SetSpecular(0.4);
	property->SetSpecularPower(20);

	vtkActor* coneActor = vtkActor::New(); //Actor
	coneActor->SetMapper(coneMapper);
	coneActor->SetProperty(property);
	coneActor->SetPosition(0, 2, 0);

	vtkRenderer* ren1 = vtkRenderer::New(); //Render
	ren1->AddActor(coneActor);
	ren1->SetBackground(0.1, 0.2, 0.4);

	vtkRenderWindow* renWin = vtkRenderWindow::New(); //Window
	renWin->AddRenderer(ren1);
	renWin->SetSize(300, 300);

	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New(); //상호작용
	iren->SetRenderWindow(renWin);

	vtkInteractorStyleTrackballCamera* style =
		vtkInteractorStyleTrackballCamera::New(); //마우스 트래킹 모드
	iren->SetInteractorStyle(style);
	iren->Initialize();
	iren->Start();

	cone->Delete();
	coneMapper->Delete();
	property->Delete();
	coneActor->Delete();
	ren1->Delete();
	renWin->Delete();
	iren->Delete();
	style->Delete();

}