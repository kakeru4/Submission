#ifndef SEA_H
#define SEA_H

#include"../Object/Object.h"

class Sea:public Object
{
public:
	Sea(D3DXVECTOR3* pos);
	virtual ~Sea();
	virtual void Control();
	virtual void Draw();

private:

};
#endif