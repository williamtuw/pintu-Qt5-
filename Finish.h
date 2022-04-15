#pragma once

#include <QDialog>
#include "ui_Finish.h"

class Finish : public QDialog
{
	Q_OBJECT

public:
	Finish(QWidget *parent = Q_NULLPTR);
	~Finish();

private:
	Ui::Finish ui;
private slots:
	void Onback();
};
