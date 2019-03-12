#include "Circle.h"


Circle::Circle(QWidget *parent) : QWidget(parent), ui(new Ui::Circle)
{
	ui->setupUi(this);

	QFont ft;
	ft.setPointSize(18);
	ui->lineEdit->setFont(ft);
	ui->Clear->setFont(ft);
}

Circle::~Circle()
{
	delete ui;
}

void Circle::setPen(QPen p)
{
	pen = p;
	update();
}

void Circle::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::red);
	painter.setPen(pen);
	painter.fillRect(90, 200, 450, 450, QColor(255, 255, 255));

	int x1, y1, x2, y2;

	if (CenterRadius.size() > 0)
	{
		x1 = CenterRadius[0].x();
		y1 = CenterRadius[0].y();
		for (int ci = x1 - 5; ci <= x1 + 5; ++ci) painter.drawPoint(ci, y1);
		for (int cj = y1 - 5; cj <= y1 + 5; ++cj) painter.drawPoint(x1, cj);//draw cross through the start point.
	}
	if (CenterRadius.size() > 1)
	{
		x2 = CenterRadius[1].x();
		y2 = CenterRadius[1].y();
		for (int ci = x2 - 5; ci <= x2 + 5; ++ci) painter.drawPoint(ci, y2);
		for (int cj = y2 - 5; cj <= y2 + 5; ++cj) painter.drawPoint(x2, cj);//draw cross through the end point.
		BresenhamCircle();
	}

	painter.end();
}

void Circle::mousePressEvent(QMouseEvent *event)
{
	QString str = "(" + QString::number(event->x()) + "," + QString::number(event->y()) + ")";
	if (event->button() == Qt::LeftButton)
	{
		ui->lineEdit->setText(tr("   LeftButton Pressed:") + str);
		CenterRadius.push_back(event->pos());

	}
	else if (event->button() == Qt::RightButton)
	{
		ui->lineEdit->setText(tr("   RightButton Pressed:") + str);
		CenterRadius.push_back(event->pos());
	}
	update();
}

void Circle::BresenhamCircle()
{
	QPainter painter(this);
	pen.setColor(Qt::darkGreen);
	painter.setPen(pen);
	painter.begin(this);

	int ox = CenterRadius[0].x();
	int oy = CenterRadius[0].y();
	int xc = CenterRadius[1].x();
	int yc = CenterRadius[1].y();
	int r = (int)sqrt((xc-ox)*(xc-ox)+(yc-oy)*(yc-oy));
	QString str;
	ui->lineEdit->setText(tr("        Circle Radius:") + str.setNum(r));

	float d = 1.25 - r;
	int x = 0, y = r;
	while (x <= y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			--y;
		}
		painter.drawPoint(ox + x, oy + y);
		painter.drawPoint(ox + x, oy - y);
		painter.drawPoint(ox - x, oy + y);
		painter.drawPoint(ox - x, oy - y);
		painter.drawPoint(ox + y, oy - x);
		painter.drawPoint(ox + y, oy + x);
		painter.drawPoint(ox - y, oy + x);
		painter.drawPoint(ox - y, oy - x);
		++x;
	}
}

void Circle::Clear_click()
{
	if (CenterRadius.size())
	{
		CenterRadius.clear();
	}
	update();
}
