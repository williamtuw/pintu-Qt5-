#pragma once

#include <QtWidgets/QWidget>
#include "ui_Gameview.h"
#include "QPainter"
#include "Gamemodel.h"
#include "Finish.h"
class Gameview : public QWidget
{
	Q_OBJECT

public:
	Gameview(QWidget *parent = Q_NULLPTR);
	bool ismousepressed,ismouseout;
	void Ccheck();
	void finished();
	QPoint pre_start;
	int pre_i, pre_j,pre_i1,pre_j1;
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void transform(const QPoint& p, int& a, int& b);
private:
	Finish * OKwin;
	Gamemodel * model;
	void paintEvent(QPaintEvent *event);
	Ui::GameviewClass ui;
private slots:
	void Onput();
	void Onrestart();
	void Oncscale(const QString&);
};
