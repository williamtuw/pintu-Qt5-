#include "Gameview.h"
#include"QFileDialog"
#include"QMouseEvent"
#include "qdebug.h"
Gameview::Gameview(QWidget *parent)
	: QWidget(parent), ismousepressed(false),ismouseout(false)
{
	ui.setupUi(this);
	OKwin = new Finish(this);
	model = new Gamemodel(QSize(width(), height()), this);
	connect(ui.btnput, &QPushButton::clicked, this, &Gameview::Onput);
	connect(ui.btnrestart, &QPushButton::clicked, this, &Gameview::Onrestart);
	connect(ui.choose, SIGNAL(currentTextChanged(const QString &)), this, SLOT(Oncscale(const QString &)));
	
}
void Gameview::paintEvent(QPaintEvent *event)
{
	//绘制3*4格子
	int scale = model->scale;
	int w = width() / (scale+1);
	int h = height() / scale;
	model->Resize(QSize(width(),height()));
	ui.btnput->move(width()-w+10,height()/2);
	ui.choose->move(width() - w+10, height() / 2-80);
	ui.btnrestart->move(width() - w+10, height() / 2-40);
	QPainter painter(this);
	QPen pen1(QBrush(QColor(0x88, 0x88, 0x88)), 4);
	painter.setPen(pen1);
	//绘出每个单元的pixmap
	//painter.setBrush(QBrush(QColor(0,0xff,0)));
	painter.setBrush(QBrush(QColor(85, 85, 255)));
	QPixmap pm_;
	int pw = model->pm.width() / scale;
	int ph = model->pm.height() / scale;
	for (int i = 0; i < scale; i++)
	{
		for (int j = 0; j < (scale+1); j++)
		{
			if(model->units[i][j].haspm)
			{
			pm_ = model->pm.copy(model->units[i][j].c*pw, model->units[i][j].r*ph, pw, ph);
			painter.drawPixmap(model->units[i][j].rect,pm_);
			//painter.drawRect(model->units[i][j].rect);
			}
			if (i == (scale-1) && j == scale)
			{
				painter.drawPixmap(model->units[i][j].rect,model->pm);
			}
		}
	}
	painter.drawRect(model->units[model->r][model->c].rect);
	//画线
	for (int i = 0; i < (scale-1); i++)
	{
		painter.drawLine(0, h + i * h, width(), h + i * h);
	}
	for (int i = 0; i < scale; i++)
	{
		painter.drawLine(w + i * w, 0, w + i * w, height());
	}
	//拖动特效
	painter.setBrush(Qt::NoBrush);
	if (ismousepressed)
	{

		QPen pen2(QBrush(QColor(0, 0xff, 0)), 4);
		painter.setPen(pen2);
		painter.drawRect(model->units[pre_i][pre_j].rect);
		if (ismouseout)
		{
			if (pre_i != model->r || pre_j != model->c)
			{
				if (pre_i1 != model->r || pre_j1 != model->c)
				{
					QPen pen3(QBrush(QColor(0xff, 0, 0)), 4);
					painter.setPen(pen3);
				}
			}
			painter.setBrush(QBrush(QColor(0x77, 0x77, 0x77, 100)));
			painter.drawRect(model->units[pre_i1][pre_j1].rect);
		}
	}
}
void Gameview::Onput() 
{
	QString qstr = QFileDialog::getOpenFileName(this, "select picture", QString(), "Images (*.png *.xpm *.jpg)");
	if (qstr == "")return ;
	model->setpm(GBK::FromUnicode(qstr).c_str());
	//setGeometry(this->x(), this->y(),model->pm.width()/2,model->pm.height()/2);
}
void Gameview::Onrestart()
{
	model->rankchange();
	update();
}
void Gameview::Oncscale(const QString& text)
{
	char str[10];
	strcpy_s(str, GBK::FromUnicode(text).c_str());
	str[1] = 0;
	int ss = atoi(str);
	model->scale = ss;
	model->Resize(QSize(width(),height()));
	model->rankchange();
	update();
}
void Gameview::mouseMoveEvent(QMouseEvent *event)
{
	int pre_i_, pre_j_;
	if (ismousepressed)
	{
		transform(event->pos(), pre_i_, pre_j_);
		if ((pre_i_ == (pre_i - 1) && pre_j_ == pre_j)
			|| (pre_i_ == (pre_i + 1) && pre_j_ == pre_j)
			|| (pre_i_ == pre_i && pre_j_ == (pre_j - 1))
			|| (pre_i_ == pre_i && pre_j_ == (pre_j + 1)))
		{
			if (!((pre_j_ == model->scale) && (pre_i_ != 0)))
			{
				pre_i1 = pre_i_;
				pre_j1 = pre_j_;
				update();
				ismouseout = true;
			}
		}
		
	}
}
void Gameview::mousePressEvent(QMouseEvent *event)
{
	pre_start = event->pos();
	transform(pre_start, pre_i, pre_j);
	qDebug() << pre_i << pre_j;
	if ((pre_i == model->r&&pre_j == model->c)
		|| (pre_i == (model->r - 1) && pre_j == model->c)
		|| (pre_i == (model->r + 1) && pre_j == model->c)
		|| (pre_i == model->r&&pre_j == (model->c - 1))
		|| (pre_i == model->r&&pre_j == (model->c + 1)))
	{
		if (!((pre_j==model->scale)&&(pre_i!=0)))
		{
			ismousepressed = true;
			update();
		}
	}
	
	
}
void Gameview::mouseReleaseEvent(QMouseEvent *event)
{
	ismousepressed = false;
	Ccheck();
	update();
}
void Gameview::transform(const QPoint& p, int& a, int& b)
{
	b = p.x() / (width() / (model->scale+1));
	a = p.y() / (height() / model->scale);
}
void Gameview::Ccheck()
{
	if (pre_i != model->r || pre_j != model->c)
	{
		if (pre_i1 == model->r&&pre_j1 == model->c)
		{
			if (ismouseout)
			{
				Gameunit u;
				u = model->units[pre_i][pre_j];
				model->units[pre_i][pre_j] = model->units[pre_i1][pre_j1];
				model->units[pre_i1][pre_j1] = u;
				model->r = pre_i;
				model->c = pre_j;
				finished();
				ismouseout = false;
			}
		}
	}
	if (pre_i == model->r&&pre_j == model->c)
	{
		if (ismouseout)
		{
			Gameunit u;
			u = model->units[pre_i][pre_j];
			model->units[pre_i][pre_j] = model->units[pre_i1][pre_j1];
			model->units[pre_i1][pre_j1] = u;
			model->r = pre_i1;
			model->c = pre_j1;
			finished();
		}
	}
	ismouseout = false;
}
void Gameview::finished()
{
	for (int i = 0; i < model->scale; i++)
	{
		for (int j = 0; j < model->scale; j++)
		{
			if (!model->units[i][j].haspm)return;
				if (model->units[i][j].r != i || model->units[i][j].c != j)
				{
					return;
				}
			
		}
	}
	OKwin->exec();
}