#ifndef FIGHTER_H
#define FIGHTER_H

#include"../Object/Object.h"

class Fighter:public Object
{
public:
	Fighter(D3DXVECTOR3* pos);
	virtual ~Fighter();
	virtual void Control();
	virtual void Draw();
private:

};
#endif