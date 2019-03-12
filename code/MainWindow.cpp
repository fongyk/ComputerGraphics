#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QFont ft;
	ft.setPointSize(18);
	ui.Line->setFont(ft);
	ui.Circle->setFont(ft);
	ui.Ellipse->setFont(ft);
	ui.Bezier->setFont(ft);
	ui.Bspline->setFont(ft);
	ui.Koch->setFont(ft);
	ui.Mandelbrot->setFont(ft);
	ui.Julia->setFont(ft);
	ui.Fern->setFont(ft);
	ui.Fill->setFont(ft);
}

void MainWindow::Line_click()
{
	getLine.show();
}
void MainWindow::Circle_click()
{
	getCircle.show();
}
void MainWindow::Ellipse_click()
{
	getEllipse.show();
}
void MainWindow::Fill_click()
{
	getFill.show();
}
void MainWindow::Bezier_click()
{
	getBezier.show();
}
void MainWindow::Bspline_click()
{
	getBspline.show();
}
void MainWindow::Koch_click()
{
	getKoch.show();
}
void MainWindow::Mandelbrot_click()
{
	getMandelbrot.show();
}
void MainWindow::Julia_click()
{
	getJulia.show();
}
void MainWindow::Fern_click()
{
	getFern.show();
}