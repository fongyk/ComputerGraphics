#include "Fill.h"

Fill::Fill(QWidget *parent) : QWidget(parent), ui(new Ui::Fill)
{
	ui->setupUi(this);
	line = new Line;

	QFont ft;
	ft.setPointSize(18);
	ui->pointNum->setFont(ft);
	ui->Clear->setFont(ft);

}
Fill:: ~Fill()
{
	delete ui;

	delete line;
}

void Fill::setPen(QPen p)
{
	pen = p;
	update();//update()更新窗口部件
}

void Fill::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		line->StartEndPoints.push_back(event->pos());
	}
	if (event->button() == Qt::MidButton)
	{
		closePolygon = true;
	}
	if (event->button() == Qt::RightButton)
	{
		fillPos.push_back(event->pos());
		fillSig = true;
	}
	
	update();
}

void Fill::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		line->StartEndPoints.push_back(event->pos());
		update();
	}
	//update();
}

void Fill::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::black);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.fillRect(90, 180, 500, 600, QColor(255, 255, 255));

	int size = (int)line->StartEndPoints.size();
	ui->pointNum->setText(tr("Point Number: ") + QString::number(size));

	if (size < 3 && fillSig == true) fillSig = false;

	if (size > 1)
	{ 
		for (int l = 2; l <= size; ++l)
		{
			line->BresenhamLine(l-2, painter);
		}
		if (closePolygon)
		{
			//QPoint tp = line->StartEndPoints[1];
			//line->StartEndPoints[1] = line->StartEndPoints[size - 1];
			//line->BresenhamLine(0, painter);
			//line->StartEndPoints[1] = tp;

			line->StartEndPoints.push_back(line->StartEndPoints[0]);
			size++;
			line->BresenhamLine(size - 2, painter);

			closePolygon = false;
		}
	}

	if (size > 2 && fillSig)
	{
		pen.setColor(Qt::blue);
		painter.setPen(pen);

		for (int k = 0; k < fillPos.size(); ++k)
		{
			seedFilling(fillPos[k], painter);
		}
		fillSig = false;
	}
	for (int i = 0; i < mapSize; ++i)
	{
		memset(line->pixelMap[i], false, sizeof(bool)*mapSize);
	}
	painter.end();
	//update();
}

void Fill::seedFilling(QPoint pos, QPainter &painter)
{
	int x = pos.x();
	int y = pos.y();

	if (x <= 90 || x >= 590 || y <= 180 || y>=780) return;
	
	if (line->pixelMap[x][y] == true) return;

	if (line->pixelMap[x][y] == false)
	{
		painter.drawPoint(QPoint(x, y));
		line->pixelMap[x][y] = true;
	}

	if ((x - 1) > 90 && line->pixelMap[x - 1][y] == false)
	{
		seedFilling(QPoint(x - 1, y), painter);
	}
	if ((x + 1) < 590 && line->pixelMap[x + 1][y] == false)
	{
		seedFilling(QPoint(x + 1, y), painter);
	}
	if ((y - 1) > 180 && line->pixelMap[x][y - 1] == false)
	{
		seedFilling(QPoint(x, y - 1), painter);
	}
	if ((y + 1) < 790 && line->pixelMap[x][y + 1] == false)
	{
		seedFilling(QPoint(x, y + 1), painter);
	}

	return;
}

void Fill::Clear_click()
{
	if (line->StartEndPoints.size())
	{
		line->StartEndPoints.clear();
	}
	if (fillPos.size())
	{
		fillPos.clear();
	}
	for (int i = 0; i < mapSize; ++i)
	{
		memset(line->pixelMap[i], false, sizeof(bool)*mapSize);
	}

	update();
}

