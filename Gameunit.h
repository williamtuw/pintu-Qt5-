#pragma once

#include <QObject>
#include "QRect"
#include "QPixmap"
class Gameunit : public QObject
{
	Q_OBJECT

public:
	const Gameunit& operator =(const Gameunit& other);
	void setrc(int i, int j);
	Gameunit(QObject *parent=NULL);
	~Gameunit();
	QRect rect;
	bool haspm;
	int r, c;
};
