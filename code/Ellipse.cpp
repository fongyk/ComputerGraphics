#include "Ellipse.h"


Ellipse::Ellipse(QWidget *parent) : QWidget(parent), ui(new Ui::Ellipse)
{
	ui->setupUi(this);

	QFont ft;
	ft.setPointSize(20);
	ui->lineEdit->setFont(ft);
	ui->ellipseCenter->setFont(ft);
	ui->aValue->setFont(ft);
	ui->bValue->setFont(ft);
	ui->Clear->setFont(ft);
}

Ellipse::~Ellipse()
{
	delete ui;
}

void Ellipse::setPen(QPen p)
{
	pen = p;
	update();
}

void Ellipse::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::red);
	painter.setPen(pen);
	painter.fillRect(250, 200, 550, 500, QColor(255, 255, 255));

	int x1, y1, x2, y2, x3, y3;

	if (TriPoints.size() > 0)
	{
		x1 = TriPoints[0].x();
		y1 = TriPoints[0].y();
		for (int ci = x1 - 5; ci <= x1 + 5; ++ci) painter.drawPoint(ci, y1);
		for (int cj = y1 - 5; cj <= y1 + 5; ++cj) painter.drawPoint(x1, cj);//draw cross through the point.
	}
	if (TriPoints.size() > 1)
	{
		x2 = TriPoints[1].x();
		y2 = TriPoints[1].y();
		for (int ci = x2 - 5; ci <= x2 + 5; ++ci) painter.drawPoint(ci, y2);//draw cross through the point.
		pen.setColor(Qt::blue);
		painter.setPen(pen);
		for (int cj = 200; cj <= 700; cj+=2) painter.drawPoint(x2, cj);//draw dashed line through the point.
	}
	if (TriPoints.size() > 2)
	{
		x3 = TriPoints[2].x();
		y3 = TriPoints[2].y();
		for (int ci = 250; ci <= 800; ci+=2) painter.drawPoint(ci, y3);//draw dashed line through the point.
		pen.setColor(Qt::red);
		painter.setPen(pen);
		for (int cj = y3 - 5; cj <= y3 + 5; ++cj) painter.drawPoint(x3, cj);//draw cross through the point.
		BresenhamEllipse();
	}

	painter.end();
}

void Ellipse::mousePressEvent(QMouseEvent *event)
{
	QString str = "(" + QString::number(event->x()) + "," + QString::number(event->y()) + ")";
	if (event->button() == Qt::LeftButton)
	{
		ui->lineEdit->setText(tr("    LeftButton Pressed:") + str);
		TriPoints.push_back(event->pos());

	}
	else if (event->button() == Qt::RightButton)
	{
		ui->lineEdit->setText(tr("    RightButton Pressed:") + str);
		TriPoints.push_back(event->pos());
	}
	update();
}

void Ellipse::BresenhamEllipse()
{
	QPainter painter(this);
	pen.setColor(Qt::darkGreen);
	painter.setPen(pen);
	painter.begin(this);

	int ox = TriPoints[0].x();
	int oy = TriPoints[0].y();
	int a = abs(TriPoints[1].x()-ox);
	int b = abs(TriPoints[2].y()-oy);

	QString str = "(" + QString::number(ox) + "," + QString::number(oy) + ")";
	ui->ellipseCenter->setText(tr(" Center:") + str);
	ui->aValue->setText(str.setNum(a));
	ui->bValue->setText(str.setNum(b));

	float d = b*b + a*a*(-b + 0.25);
	int x = 0, y = b, fx = a*a / sqrt((float)a*a + b*b);
	while (b*b*(x + 1) < a*a*(y - 0.5))
	{
		if (d < 0)
			d += b*b*(2 * x + 3);
		else
		{
			d += b*b*(2 * x + 3) + a*a*(-2 * y + 2);
			--y;
		}
		++x;
		painter.drawPoint(ox + x, oy + y);
		painter.drawPoint(ox - x, oy + y);
		painter.drawPoint(ox + x, oy - y);
		painter.drawPoint(ox - x, oy - y);
	}
	d = b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y - 1) - a*a*b*b;
	d = b*b*(0.25*x) + a*a*(1-2*y);
	while (y > 0)
	{
		if (d < 0)
		{
			++x;
			d += b*b*(2 * x + 2) + a*a*(-2 * y + 3);
		}
		else
			d += a*a*(-2 * y + 3);
		--y;
		painter.drawPoint(ox + x, oy + y);
		painter.drawPoint(ox - x, oy + y);
		painter.drawPoint(ox + x, oy - y);
		painter.drawPoint(ox - x, oy - y);
	}
}

void Ellipse::Clear_click()
{
	if (TriPoints.size())
	{
		TriPoints.clear();
	}
	update();
}
