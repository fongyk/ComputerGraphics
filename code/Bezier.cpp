#include "Bezier.h"

Bezier::Bezier(QWidget *parent) : QWidget(parent), ui(new Ui::Bezier)
{
	ui->setupUi(this);
	line = new Line;

	QFont ft;
	ft.setPointSize(18);
	ui->lineEdit->setFont(ft);
	ui->Clear->setFont(ft);
}

Bezier::~Bezier()
{
	delete ui;
	delete line;
}

void Bezier::setPen(QPen p)
{
	pen = p;
	update();
}

void Bezier::mousePressEvent(QMouseEvent* event)
{
	QString str = "(" + QString::number(event->x()) + "," + QString::number(event->y()) + ")";
	if (event->button() == Qt::LeftButton)
	{
		ui->lineEdit->setText(tr("   LeftButton Pressed:") + str);
		line->StartEndPoints.push_back(event->pos());
	}
	if (event->button() == Qt::RightButton)
	{
		ui->lineEdit->setText(tr("   RightButton Pressed:") + str);
		curveStatus = true;
	}
	if (event->button() == Qt::MidButton)
	{
		ui->lineEdit->setText(tr("   MidButton Pressed:") + str);
		closePolygon = true;
	}
	update();
}

void Bezier::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	painter.setPen(pen);
	painter.fillRect(80, 190, 500, 480, QColor(255, 255, 255));

	int size = line->StartEndPoints.size();
	if (size > 0)
	{
		pen.setColor(Qt::red);
		pen.setWidth(4);
		painter.setPen(pen);
		for (int p = 0; p < size; ++p)
		{
			painter.drawPoint(line->StartEndPoints[p]);
		}
	}
	if (size > 1)
	{
		pen.setColor(Qt::darkGreen);
		pen.setWidth(1);
		painter.setPen(pen);
		for (int l = 0; l < size - 1; ++l)
		{
			line->BresenhamLine(l, painter);
		}
		if (closePolygon)
		{
			line->StartEndPoints.push_back(line->StartEndPoints[0]);
			size++;
			line->BresenhamLine(size - 2, painter);

			closePolygon = false;
		}

	}
	if (size > 1 && curveStatus == true)
	{
		pen.setColor(Qt::blue);
		painter.setPen(pen);
		BezierCurve(line->StartEndPoints, painter);
		curveStatus = false;
	}
	painter.end();
}

inline int Factorial(int n)
{
	if (n == 0) return 1;
	int x = 1;
	for (int i = 1; i <= n; ++i)
	{
		x *= i;
	}
	return x;
}

void Bezier::BezierCurve(QVector<QPoint> P, QPainter &painter)
{
	int n = P.size() - 1;
	//for (double u = 0; u <= 1; u += du)
	//{
	//	double xu = 0.0;
	//	double yu = 0.0;
	//	for (int i = 0; i <= n; ++i)
	//	{
	//		double C = Factorial(n) / (Factorial(i) * Factorial(n - i));
	//		double B = C * pow(u, i) * pow(1 - u, n - i);
	//		xu += B * P[i].x();
	//		yu += B * P[i].y();
	//	}
	//	painter.drawPoint(QPoint(xu, yu));
	//}
	double *px = new double[n + 1];
	double *py = new double[n + 1];
	for (double u = 0; u <= 1; u += du)
	{
		for (int k = 0; k < n + 1; ++k)
		{
			px[k] = P[k].x();
			py[k] = P[k].y();
		}
		for (int r = 1; r <= n; ++r)
		{
			int i = 0;
			while (i <= n - r)
			{
				px[i] = (1 - u) * px[i] + u * px[i + 1];
				py[i] = (1 - u) * py[i] + u * py[i + 1];
				++i;
			}
		}
		painter.drawPoint(QPoint(px[0], py[0]));
	}
	delete px; px = nullptr;
	delete py; py = nullptr;

}

void Bezier::Clear_click()
{
	if (line->StartEndPoints.size())
	{
		line->StartEndPoints.clear();
	}
	update();
}


