#pragma once

#include "CoreMinimal.h"
#include "HuntZoneManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerEnteredHuntingZone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerLeftHuntingZone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDangerLevelHasChanged,float, NewDangerLevel);


class AHuntZone;
/**
 *
 */
UCLASS(Blueprintable)
class PROJECTWINTER_API UHuntZoneManager : public UObject
{
	GENERATED_BODY()
public:
	static UHuntZoneManager* GetInstance();



	void AddActiveHuntingZone(AHuntZone* Zone);
	void RemoveActiveHuntingZone(AHuntZone* Zone);
	bool IsPlayerInAnyHuntingZone() const;
	float GetCurrentDangerLevel();
	void ResetHuntZones();

	UPROPERTY(BlueprintAssignable, Category="Winter|Hunt Zone")
	FPlayerEnteredHuntingZone OnPlayerEnteredHuntingZone;

	UPROPERTY(BlueprintAssignable, Category="Winter|Hunt Zone")
	FPlayerLeftHuntingZone OnPlayerLeftHuntingZone;

	UPROPERTY(BlueprintAssignable, Category="Winter|Hunt Zone")
	FDangerLevelHasChanged OnDangerLevelHasChanged;

private:
	UHuntZoneManager();
	void SetCurrentDangerLevel();
	float CurrentDangerLevel = 0.f;
	static UHuntZoneManager* Instance;
	TArray<AHuntZone*> ActiveHuntingZones;
};
