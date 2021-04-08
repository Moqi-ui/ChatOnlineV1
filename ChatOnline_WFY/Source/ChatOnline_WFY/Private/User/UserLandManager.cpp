
#include "UserLandManager.h"


void FUserLandManager::Tick(float DaltaTime)
{

}

ETickableTickType FUserLandManager::GetTickableTickType() const
{
	return ETickableTickType::Always;
}

TStatId FUserLandManager::GetStatId() const 
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FUserLandManager, STATGROUP_Tickables);
}