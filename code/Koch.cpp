#include "Koch.h"

Koch::Koch(QWidget *parent) : QWidget(parent), ui(new Ui::Koch)
{
	ui->setupUi(this);
	line = new Line;

	QFont ft;
	ft.setPointSize(18);
	ui->Clear->setFont(ft);
	ui->levelZero->setFont(ft);
	ui->levelOne->setFont(ft);
	ui->levelTwo->setFont(ft);
	ui->levelThree->setFont(ft);
	ui->levelFour->setFont(ft);
}

Koch::~Koch()
{
	delete ui;
	delete line;
}

void Koch::setPen(QPen p)
{
	pen = p;
	update();
}

void Koch::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::blue);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.fillRect(60, 210, 620, 600, QColor(255, 255, 255));

	int ox = 360, oy = 520;
	line->StartEndPoints.push_back(QPoint(ox, oy - 200));
	line->StartEndPoints.push_back(QPoint(ox - 100 * sqrt(3), oy + 100));
	line->StartEndPoints.push_back(QPoint(ox + 100 * sqrt(3), oy + 100));
	line->StartEndPoints.push_back(QPoint(ox, oy - 200));
	if (level >= 0)
	{
		KochGraphic(line->StartEndPoints, painter, level);
		level = -1;
		int size = line->StartEndPoints.size();
		for (int l = 0; l < size - 1; ++l)
		{
			line->BresenhamLine(l, painter);
		}
		line->StartEndPoints.clear();
	}
	painter.end();
}

void Koch::KochGraphic(QVector<QPoint> &P, QPainter& painter, char level)
{
	if (level == 0) return;
	QVector<QPoint> tmpP(P);
	int size = tmpP.size();
	for (int i = 0; i < size-1;++i)
	{
		int offset = i * 4 + 1;

		QPoint p1 = tmpP[i];
		QPoint p2 = tmpP[i + 1];
		int stepX = abs(p1.x() - p2.x()) / 3;

		QPoint tp1, tp2, tp3;

		bool flagX, flagY;
		if (p1.y() == p2.y())
		{
			flagX = (p1.x() < p2.x()) ? true : false;
			if (flagX == true)
			{
				tp1 = QPoint(p1.x() + stepX, p1.y());
				tp2 = QPoint((p1.x()+p2.x())/2, p1.y() + stepX*(sqrt(3)/2));
				tp3 = QPoint(p2.x() - stepX, p2.y());
			}
			else
			{
				tp1 = QPoint(p1.x() - stepX, p1.y());
				tp2 = QPoint((p1.x() + p2.x()) / 2, p1.y() - stepX*(sqrt(3) / 2));
				tp3 = QPoint(p2.x() + stepX, p2.y());
			}
		}
		else
		{
			int stepY = abs(p1.y() - p2.y()) / 3;

			flagY = (p1.y() > p2.y()) ? true : false;
			if (flagY == true)
			{
				if (p1.x() < p2.x())
				{
					tp1 = QPoint(p1.x() + stepX, p1.y() - stepY);
					tp2 = QPoint(p2.x(), p1.y() - stepY);
					tp3 = QPoint(p2.x() - stepX, p2.y() + stepY);
				}
				else
				{
					tp1 = QPoint(p1.x() - stepX, p1.y() - stepY);
					tp2 = QPoint(p1.x(), p2.y() + stepY);
					tp3 = QPoint(p2.x() + stepX, p2.y() + stepY);
				}
			}
			else
			{
				if (p1.x() < p2.x())
				{
					tp1 = QPoint(p1.x() + stepX, p1.y() + stepY);
					tp2 = QPoint(p1.x(), p2.y() - stepY);
					tp3 = QPoint(p2.x() - stepX, p2.y() - stepY);
				}
				else
				{
					tp1 = QPoint(p1.x() - stepX, p1.y() + stepY);
					tp2 = QPoint(p2.x(), p1.y() + stepY);
					tp3 = QPoint(p2.x() + stepX, p2.y() - stepY);
				}
			}
		}
		P.insert(P.begin() + offset, tp3);
		P.insert(P.begin() + offset, tp2);
		P.insert(P.begin() + offset, tp1);
	}

	QVector<QPoint>().swap(tmpP);
	--level;
	KochGraphic(P, painter, level);
}

void Koch::LevelZero_click()
{
	level = 0;
	update();
}
void Koch::LevelOne_click()
{
	level = 1;
	update();
}
void Koch::LevelTwo_click()
{
	level = 2;
	update();
}
void Koch::LevelThree_click()
{
	level = 3;
	update();
}
void Koch::LevelFour_click()
{
	level = 4;
	update();
}

void Koch::Clear_click()
{
	if (line->StartEndPoints.size())
	{
		line->StartEndPoints.clear();
	}
	level = -1;
	update();
}


