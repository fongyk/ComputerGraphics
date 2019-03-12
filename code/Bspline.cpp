#include "Bspline.h"

Bspline::Bspline(QWidget *parent) : QWidget(parent), ui(new Ui::Bspline)
{
	ui->setupUi(this);
	line = new Line;

	QFont ft;
	ft.setPointSize(18);
	ui->Clear->setFont(ft);
}

Bspline::~Bspline()
{
	delete ui;
	delete line;
}

void Bspline::setPen(QPen p)
{
	pen = p;
	update();
}

void Bspline::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		line->StartEndPoints.push_back(event->pos());
	}
	if (event->button() == Qt::RightButton)
	{
		curveStatus = true;
	}
	update();
}

void Bspline::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	painter.setPen(pen);
	painter.fillRect(75, 150, 500, 500, QColor(255, 255, 255));

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
	}
	if (size > 1 && curveStatus == true)
	{
		pen.setColor(Qt::blue);
		pen.setWidth(2);
		painter.setPen(pen);
		QVector<QPoint> P(line->StartEndPoints);
		line->StartEndPoints.clear();
		BsplineCurve(P, painter);
		QVector<QPoint>().swap(P);
		curveStatus = false;
	}
	painter.end();
}

void Bspline::BsplineCurve(QVector<QPoint> P, QPainter &painter)
{
	int pn = P.size();
	double *knots = new double[pn + order + 1];

	for (int i = 0; i < pn + order + 1; i++)
	{
		knots[i] = i * 1.0 / (pn + order);
	}

	int pos_i;
	QPoint p0, p1;
	for (double u = knots[order]; u <= knots[pn]; u += du2)
	{
		for (pos_i = 0; pos_i < pn + order; pos_i++)
		{
			if (u >= knots[pos_i] && u <= knots[pos_i + 1])
			{
				break;
			}
		}
		QPoint outP;

		DeBoor(order-1, pos_i, u, knots, P, pn, &outP);

		if (u == knots[order])
		{
			p0 = outP;
			line->StartEndPoints.push_back(p0);
		}
		else
		{
			p1 = outP;
			line->StartEndPoints.push_back(p1);
			line->BresenhamLine(line->StartEndPoints.size()-2, painter);
			p0 = p1;
		}
	}
	line->StartEndPoints.clear();
}

void Bspline::DeBoor(int k, int i, double u, double *knots, QVector<QPoint> P, int pn, QPoint *outP)
{
	if (k == 0)
	{
		*outP = P[i];
		return;
	}
	double alpha = (u - knots[i]) / (knots[i + order - k] - knots[i]);

	QVector<QPoint> newP1;
	QVector<QPoint> newP2;

	for (int j = 0; j < pn; j++)
	{
		newP1.push_back(P[j] * (1 - alpha));
		newP2.push_back(P[j] * alpha);
	}

	QPoint outP1 = QPoint(0, 0), outP2 = QPoint(0, 0);

	DeBoor(k - 1, i - 1, u, knots, newP1, pn, &outP1);
	DeBoor(k - 1, i, u, knots, newP2, pn, &outP2);

	*outP = outP1 + outP2;
}


void Bspline::Clear_click()
{
	if (line->StartEndPoints.size())
	{
		line->StartEndPoints.clear();
	}
	update();
}


