#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "HuntZone.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class PROJECTWINTER_API AHuntZone : public ATriggerBox
{
	GENERATED_BODY()
public:
	AHuntZone();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Winter|Hunting Zone")
	float DangerLevel = 0.0;

	UFUNCTION()
	void OnPlayerEnterZone(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnPlayerExitZone(AActor* OverlappedActor, AActor* OtherActor);

private:
	bool IsOtherActorThePlayer(AActor* OtherActor) const;

};
