#include "Gamemodel.h"

Gamemodel::Gamemodel(const QSize& p, QObject *parent)
	: QObject(parent)
{
	scale = 3;
	srand(time(NULL));
	size = p;
	int w = size.width() / (scale+1);
	int h = size.height() / scale;
	for (int i = 0; i < scale; i++)
	{
		for (int j = 0; j < (scale+1); j++)
		{
			units[i][j].rect.setSize(QSize(w, h));
			units[i][j].rect.moveTo(j*w, i*h);
			//units[i][j].setrc(i, j);
		}
	}
	units[0][scale].haspm = false;
	r = 0;
	c = scale;
}
Gamemodel::~Gamemodel()
{
}
void Gamemodel::rankchange()
{
	Resize(size);
	int rank[81], a, b, c;
	for (int j = 0; j < (scale*scale); j++)
	{
		rank[j] = j;
	}
	for (int i = 0; i < 2000; i++)
	{
		a = rand() % (scale*scale);
		b = rand() % (scale*scale);
		if (a == (scale-1) || b == (scale-1))
		{
			continue;
		}
		if (a != b)
		{
			c = rank[a];
			rank[a] = rank[b];
			rank[b] = c;
		}

	}
	for (int i = 0; i < (scale*scale); i++)
	{
		units[i / scale][i % scale].r = rank[i] / scale;
		units[i / scale][i % scale].c = rank[i] % scale;
		units[i / scale][i % scale].haspm = true;
	}
	units[0][scale].haspm = false;
	this->r = 0;
	this->c = scale;
	int count = 0,flag=1;
	while (1)
	{
		flag = 1;
		for (int i = 0; i < (scale*scale); i++)
		{
			if (rank[i] != i)
			{
				int h = rank[rank[i]];
				rank[rank[i]] = rank[i];
				rank[i] = h;
				flag = 0;
				break;
			}
		}
		if (flag)break;
		count++;
	}
	if (count % 2)
	{
		rankchange();
	}
}
int Gamemodel::Resize(const QSize& s)
{
	size = s;
	int w = size.width() / (scale+1);
	int h = size.height() / scale;
	for (int i = 0; i < scale; i++)
	{
		for (int j = 0; j < (scale+1); j++)
		{
			units[i][j].rect.setSize(QSize(w, h));
			units[i][j].rect.moveTo(j*w, i*h);
		}
	}
	return 0;
}
int Gamemodel::setpm(const char* path)
{
	pm.load(GBK::ToUnicode(path));
	rankchange();
	return 0;
}