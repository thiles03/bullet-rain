#include "BR_GameMode_Base.h"

int ABR_GameMode_Base::GetKillCount() 
{
	return KillCount;
}

int ABR_GameMode_Base::GetHighKillCount() 
{
	return HighestKillCount;  
}

void ABR_GameMode_Base::SetKillCount(int Value) 
{
	KillCount += Value;
}

void ABR_GameMode_Base::SetHighKillCount(int Value) 
{
	HighestKillCount = Value;
}
