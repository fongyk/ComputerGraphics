#include "Line.h"

Line::Line(QWidget *parent) : QWidget(parent),	ui(new Ui::Line)
{
    ui->setupUi(this);

	QFont ft;
	ft.setPointSize(18);
	ui->lineEdit->setFont(ft);
	ui->Clear->setFont(ft);

	pixelMap = new bool*[mapSize];
	for (int i = 0; i < mapSize; ++i)
	{
		pixelMap[i] = new bool[mapSize];
		memset(pixelMap[i], false, sizeof(pixelMap[i][0])*mapSize);
	}
	
}

Line::~Line()
{
    delete ui;
	for (int i = 0; i < mapSize; ++i)
	{
		delete[] pixelMap[i];
		pixelMap[i] = nullptr;
	}
	delete[] pixelMap;
	pixelMap = nullptr;
}

void Line::setPen(QPen p)
{
    pen=p;
    update();
}

void Line::paintEvent(QPaintEvent *event)
{
    QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::red);
	pen.setWidth(5);
	painter.setPen(pen);
	painter.fillRect(90, 160, 450, 450, QColor(255, 255, 255));

    int x1,y1,x2,y2;

	int size = StartEndPoints.size();
    if (size > 0 && size%2==0)
    {
		painter.drawPoint(StartEndPoints[size - 2]);
		pixelMap[StartEndPoints[size - 2].x()][StartEndPoints[size - 2].y()] = true;
		painter.drawPoint(StartEndPoints[size - 1]);
		pixelMap[StartEndPoints[size - 1].x()][StartEndPoints[size - 1].y()] = true;
		pen.setColor(Qt::darkGreen);
		pen.setWidth(1);
		painter.setPen(pen);
		BresenhamLine(size - 2, painter);
		for (int i = 0; i < mapSize; ++i)
		{
			memset(pixelMap[i], false, sizeof(bool)*mapSize);
		}
    }

	painter.end();
}

void Line::mousePressEvent(QMouseEvent *event)
{
	QString str = "(" + QString::number(event->x()) + "," + QString::number(event->y()) + ")";
	if (event->button() == Qt::LeftButton)
    {
		ui->lineEdit->setText(tr("   LeftButton Pressed:") + str);
		StartEndPoints.push_back(event->pos());

    }
	else if (event->button() == Qt::RightButton)
    {
		ui->lineEdit->setText(tr("   RightButton Pressed:") + str);
		StartEndPoints.push_back(event->pos());
    }
    update();
}

void Line::BresenhamLine(int pos, QPainter& painter)
{
    int x1,y1,x2,y2;
    x1=StartEndPoints[pos].x();
    y1=StartEndPoints[pos].y();
    x2=StartEndPoints[pos+1].x();
    y2=StartEndPoints[pos+1].y();

	int dy = abs(y2 - y1);
	int dx = abs(x2 - x1);

	painter.drawPoint(QPoint(x1, y1));
	pixelMap[x1][y1] = true;

    if (abs(y2-y1) <= abs(x2-x1))// slope |m|<=1
    {
        if (x1>x2)
        {
			std::swap(x1, x2);
			std::swap(y1, y2);
        }

        int p=dy*2-dx;
        int yk=y1;

        for (int i=x1+1;i<=x2;i++)
        {
            if (p>=0)
            {
                p=p+2*dy-2*dx;
            }
            else
            {
                p=p+2*dy;
            }
            if (p>=0)
            {
                if (y2>=y1)
                {
                    yk++;
                }
                else
                {
                    yk--;
                }
            }
            painter.drawPoint(QPoint(i,yk));
			pixelMap[i][yk] = true;
        }
        //painter.end();
    }
    else// slope |m|>1
    {
        if (y1>y2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

        int p=dx*2-dy;

        int xk=x1;
        for (int i=y1+1;i<=y2;i++)
        {
            if (p>=0)
            {
                p=p+2*dx-2*dy;
            }
            else
            {
                p=p+2*dx;
            }
            if (p>=0)
            {
                if (x2>=x1)
                {
                    xk++;
                }
                else
                {
                    xk--;
                }
            }
            painter.drawPoint(QPoint(xk,i));
			pixelMap[xk][i] = true;
        }
        //painter.end();
    }
     //update();

}

void Line::Clear_click()
{
    if(StartEndPoints.size())
    {
        StartEndPoints.clear();
    }
	//std::fill_n(&pixelMap[0][0], mapSize*mapSize, false);
	for (int i = 0; i < mapSize; ++i)
	{
		memset(pixelMap[i], false, sizeof(bool)*mapSize);
	}
    update();
}
