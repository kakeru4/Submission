#include"Sea.h"
#include"../Lib/Lib.h"
Sea::Sea(D3DXVECTOR3* pos)
	:Object(pos)
{
	Lib::GetInstance().LoadXFile(2,"../Resouce//Sea.x");
}

Sea::~Sea()
{

}

void Sea::Control()
{

}

void Sea::Draw()
{
	TransWorld(m_ObjectPos);
	Lib::GetInstance().DrawXFile(2);
}