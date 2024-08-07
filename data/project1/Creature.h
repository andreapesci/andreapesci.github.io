#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Creature.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerStartedLookingAtCreature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerStoppedLookingAtCreature);

UCLASS()
class PROJECTWINTER_API ACreature : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PerformAttack();

	bool IsPlayerInAttackRange() const;

	bool IsPlayerLookingAtCreature() const;

	UPROPERTY(BlueprintAssignable, Category="Winter|Combat")
	FPlayerStartedLookingAtCreature OnPlayerStartedLookingAtCreature;

	UPROPERTY(BlueprintAssignable, Category="Winter|Combat")
	FPlayerStoppedLookingAtCreature OnPlayerStoppedLookingAtCreature;

private:
	UPROPERTY(EditAnywhere, Category = "Winter|Components")
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Winter|Components")
	TObjectPtr<class USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, Category="Winter|Combat|Lowest Danger")
	float AttackRangeLowestDanger;
	UPROPERTY(EditAnywhere, Category="Winter|Combat|Lowest Danger")
	float TimeToAttackLowestDanger;
	UPROPERTY(EditAnywhere, Category="Winter|Combat|Lowest Danger")
	float TimeToAttackWhenSeenLowestDanger;

	UPROPERTY(EditAnywhere, Category="Winter|Combat|Highest Danger")
	float AttackRangeHighestDanger;
	UPROPERTY(EditAnywhere, Category="Winter|Combat|Highest Danger")
	float TimeToAttackHighestDanger;
	UPROPERTY(EditAnywhere, Category="Winter|Combat|Highest Danger")
	float TimeToAttackWhenSeenHighestDanger;

	UPROPERTY(EditAnywhere, Category="Winter|Combat")
	float ViewAngleTriggerEffects = 40.f;

	UFUNCTION()
	void OnCurrentDangerChange(float NewDanger);

	float TimePlayerInRange = 0.f;
	float TimePlayerLookingAtCreature = 0.f;
	bool bCreatureHasAttacked = false;
	float CurrentDanger = 0.f;
};
