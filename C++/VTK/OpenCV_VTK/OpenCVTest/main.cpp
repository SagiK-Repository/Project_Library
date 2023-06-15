#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
#include <vtkConeSource.h>
#include <vtkChartXYZ.h>
#include <vtkContextMouseEvent.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPen.h>
#include <vtkPlotSurface.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>
#include <vtkUnsignedCharArray.h>
#include <vtkVector.h>

#include <opencv2/opencv.hpp>
#include <time.h>
#include "ValueI.h"
using namespace cv;  // cv 안써도 됨
using namespace std; //std 안써도 됨

#pragma warning (disable:4819) //경고 메시지 숨기기
#pragma warning (disable:4996) //경고 메시지 숨기기


int main() {
	
	//z=sinx+cosx
	if(i==1) {
		vtkNew<vtkNamedColors> colors;

		vtkNew<vtkChartXYZ> chart;
		chart->SetGeometry(vtkRectf(10.0, 10.0, 630, 470));

		vtkNew<vtkPlotSurface> plot;

		vtkNew<vtkContextView> view;
		view->GetRenderer()->SetBackground(colors->GetColor3d("Silver").GetData());
		view->GetRenderWindow()->SetSize(640, 480);
		view->GetScene()->AddItem(chart);

		// Create a surface
		vtkNew<vtkTable> table;
		vtkIdType numPoints = 70;
		for (vtkIdType i = 0; i < numPoints; ++i)
		{
			vtkNew<vtkFloatArray> arr;
			table->AddColumn(arr);
		}


		float d = 10.0;
		table->SetNumberOfRows(static_cast<vtkIdType>(numPoints));
		for (vtkIdType i = 0; i < numPoints; ++i)
		{
			float x = i / 70.0 *d;
			cout << x << endl;
			for (vtkIdType j = 0; j < numPoints; ++j)
			{
				float y = j / 70.0 * d;
				table->SetValue(i, j, ( sin(x)+cos(y) )/10);
			}
		}

		// Set up the surface plot we wish to visualize and add it to the chart.
		plot->SetXRange(0, 1.0);
		plot->SetYRange(0, 1.0);
		plot->SetInputData(table);
		plot->GetPen()->SetColorF(colors->GetColor3d("Tomato").GetData());
		chart->AddPlot(plot);

		view->GetRenderWindow()->SetMultiSamples(0);
		view->GetInteractor()->Initialize();
		view->GetRenderWindow()->SetWindowName("SurfacePlot");
		view->GetRenderWindow()->Render();

		// rotate
		vtkContextMouseEvent mouseEvent;
		mouseEvent.SetInteractor(view->GetInteractor());

		vtkVector2i pos;

		vtkVector2i lastPos;
		mouseEvent.SetButton(vtkContextMouseEvent::LEFT_BUTTON);
		lastPos.Set(100, 50);
		mouseEvent.SetLastScreenPos(lastPos);
		pos.Set(150, 100);
		mouseEvent.SetScreenPos(pos);

		vtkVector2d sP(pos.Cast<double>().GetData());
		vtkVector2d lSP(lastPos.Cast<double>().GetData());
		vtkVector2d screenPos(mouseEvent.GetScreenPos().Cast<double>().GetData());
		vtkVector2d lastScreenPos(
			mouseEvent.GetLastScreenPos().Cast<double>().GetData());

		chart->MouseMoveEvent(mouseEvent);

		view->GetInteractor()->Start();
	}

	if (i == 0) {
		Mat image;
		image = imread("C:/opencv453/sources/samples/data/HappyFish.jpg",0);
		imshow("Test", image);

		waitKey(100);

		Mat Re = image.clone();
		Re.convertTo(Re, CV_32F);
		resize(Re, Re, Size(200, 200));

		vtkNew<vtkNamedColors> colors;

		vtkNew<vtkChartXYZ> chart;
		chart->SetGeometry(vtkRectf(10.0, 10.0, 630, 470));

		vtkNew<vtkPlotSurface> plot;

		vtkNew<vtkContextView> view;
		view->GetRenderer()->SetBackground(colors->GetColor3d("Silver").GetData());
		view->GetRenderWindow()->SetSize(640, 480);
		view->GetScene()->AddItem(chart);

		// Create a surface
		vtkNew<vtkTable> table;
		int wh = 200;
		vtkIdType numPoints = wh;
		for (vtkIdType i = 0; i < numPoints; ++i)
		{
			vtkNew<vtkFloatArray> arr;
			table->AddColumn(arr);
		}


		float d = 10.0;
		table->SetNumberOfRows(static_cast<vtkIdType>(numPoints));
		for (vtkIdType i = 0; i < numPoints; ++i)
		{
			float x = i / (float)wh * d;
			for (vtkIdType j = 0; j < numPoints; ++j)
			{
				float y = j / (float)wh * d;
				table->SetValue(i, j, Re.at<float>(j, i) / 255);
			}
		}

		// Set up the surface plot we wish to visualize and add it to the chart.
		plot->SetXRange(0, 1.0);
		plot->SetYRange(0, 1.0);
		plot->SetInputData(table);
		plot->GetPen()->SetColorF(colors->GetColor3d("Tomato").GetData());
		chart->AddPlot(plot);

		view->GetRenderWindow()->SetMultiSamples(0);
		view->GetInteractor()->Initialize();
		view->GetRenderWindow()->SetWindowName("SurfacePlot");
		view->GetRenderWindow()->Render();


		waitKey();
	}

	return 0;

}


