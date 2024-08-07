#include "Creature/HuntZoneManager.h"

#include "Creature/HuntZone.h"

UHuntZoneManager* UHuntZoneManager::Instance = nullptr;

UHuntZoneManager* UHuntZoneManager::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UHuntZoneManager>();
		Instance->AddToRoot();


	}
	return Instance;
}

void UHuntZoneManager::ResetHuntZones()
{
	ActiveHuntingZones.Empty();
}




void UHuntZoneManager::AddActiveHuntingZone(AHuntZone* Zone)
{
	if (ActiveHuntingZones.Contains(Zone))
	{
		return;
	}
	ActiveHuntingZones.Add(Zone);
	SetCurrentDangerLevel();
	if (ActiveHuntingZones.Num() == 1)
	{
		OnPlayerEnteredHuntingZone.Broadcast();
	}

}

void UHuntZoneManager::RemoveActiveHuntingZone(AHuntZone* Zone)
{

	ActiveHuntingZones.Remove(Zone);
	SetCurrentDangerLevel();
	if (!IsPlayerInAnyHuntingZone())
	{
		OnPlayerLeftHuntingZone.Broadcast();
	}

}

bool UHuntZoneManager::IsPlayerInAnyHuntingZone() const
{
	return ActiveHuntingZones.Num() > 0;
}

float UHuntZoneManager::GetCurrentDangerLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Current Danger Level: %f"), CurrentDangerLevel );
	return CurrentDangerLevel;
}



UHuntZoneManager::UHuntZoneManager()
{
}

void UHuntZoneManager::SetCurrentDangerLevel()
{
	if (ActiveHuntingZones.Num() == 0)
	{
		CurrentDangerLevel = 0.f;
		OnDangerLevelHasChanged.Broadcast(CurrentDangerLevel);
		return;
	}

	float MaxFoundDanger = ActiveHuntingZones[0]->DangerLevel;
	for (const AHuntZone* Zone : ActiveHuntingZones)
	{
		if (Zone && Zone->DangerLevel > CurrentDangerLevel)
		{
			MaxFoundDanger = Zone->DangerLevel;
		}
	}
	CurrentDangerLevel = MaxFoundDanger;
	GetCurrentDangerLevel();
	OnDangerLevelHasChanged.Broadcast(CurrentDangerLevel);
}
