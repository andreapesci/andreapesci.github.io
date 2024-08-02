// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "UObject/NoExportTypes.h"
#include "CreatureManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreatureHasSpawned, ACreature*, Creature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreatureHasDespawned, ACreature*, Creature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTWINTER_API UCreatureManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCreatureManagerComponent();

protected:
	virtual void BeginPlay() override;

public:


	void PlayerEnteredHuntingZone();
	void PlayerLeftHuntingZone();
	void DangerLevelHasChanged(const float& NewDanger) const;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Winter|Spawn Properties")
	TSubclassOf<ACreature> CreatureClass;

	UPROPERTY(BlueprintAssignable, Category="Winter|Combat")
	FCreatureHasSpawned OnCreatureHasSpawned;

	UPROPERTY(BlueprintAssignable, Category="Winter|Combat")
	FCreatureHasDespawned OnCreatureHasDespawned;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Winter|Audio")
	TObjectPtr<UAudioComponent> EnvironmentSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Winter|Audio")
	TObjectPtr<UAudioComponent> HeartBeat;
private:
	UPROPERTY()
	TObjectPtr<ACreature> SpawnedCreature;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle DespawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float MinimumSpawnCreatureTimerAtLowestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float MaximumSpawnCreatureTimerAtLowestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float MinimumDespawnCreatureTimerAtLowestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float MaximumDespawnCreatureTimerAtLowestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float MinimumSpawnCreatureRadiusAtLowestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float MaximumSpawnCreatureRadiusAtLowestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float SpawnsNeededForVirtualSafeToReachPlayerAtLowestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Lowest Danger")
	float EscapeZoneRadiusAtLowestDanger;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float MinimumSpawnCreatureTimerAtHighestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float MaximumSpawnCreatureTimerAtHighestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float MinimumDespawnCreatureTimerAtHighestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float MaximumDespawnCreatureTimerAtHighestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float MinimumSpawnCreatureRadiusAtHighestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float MaximumSpawnCreatureRadiusAtHighestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float SpawnsNeededForVirtualSafeToReachPlayerAtHighestDanger;
	UPROPERTY(EditAnywhere, Category = "Winter|Spawn Properties|Highest Danger")
	float EscapeZoneRadiusAtHighestDanger;

	UPROPERTY(EditAnywhere, Category = "Winter|Debug Properties")
	float DebugTimeDurationInSeconds = 0.f;

	UPROPERTY(EditAnywhere,  Category = "Winter|Audio|Lowest Danger")
	float HeartBeatLowestDangerRhythm = 1.f;
	UPROPERTY(EditAnywhere,  Category = "Winter|Audio|Lowest Danger")
	float HeartBeatLowestDangerVolume = 1.f;
	UPROPERTY(EditAnywhere,  Category = "Winter|Audio|Highest Danger")
	float HeartBeatHighestDangerRhythm = 3.f;
	UPROPERTY(EditAnywhere,  Category = "Winter|Audio|Highest Danger")
	float HeartBeatHighestDangerVolume = 3.f;


	void SpawnCreature();
	void DespawnCreature();
	void StartSpawnLogic();
	void StopSpawnLogic();
	void CalculateRandomValueInRangeBasedOnDanger(float& OutRandomValue, const float& MinValueLowestEnd, const float& MaxValueLowestEnd, const float& MinValueHighestEnd, const float& MaxValueHighestEnd) const;
	void CalculateRandomSpawnLocationAndRotation(FVector& RandomSpawnLocation,FRotator& RandomSpawnRotation);
	bool IsCreatureStillInZoneAtDespawn();

	bool bShouldSpawn = false;
	float LastMinimumSpawnLocation;
	float LastMaximumSpawnLocation;
	int SameZoneSpawnsCounter = 0;
	float TraceHeight = 1000.0f;


	FVector GenerateSpawnLocationInCone(const FVector& PlayerLocation,const FVector& PlayerForward,const float& MinDistance,const float& MaxDistance,const float& LeftAngle,const float& RightAngle);
};
