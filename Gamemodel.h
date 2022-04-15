#pragma once

#include <QObject>
#include "Gameunit.h"
#include "GBK.h"
class Gamemodel : public QObject
{
	Q_OBJECT

public:
	int setpm(const char* path);
	Gamemodel(const QSize& p,QObject *parent);
	~Gamemodel();
	void rankchange();
	int scale;
	Gameunit units[9][10];
	QSize size;
	QPixmap pm;
	int r, c;
	int Resize(const QSize& s);
};
