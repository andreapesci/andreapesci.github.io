#include "Creature/HuntZone.h"

#include "Creature/HuntZoneManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AHuntZone::AHuntZone()
{
}

void AHuntZone::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AHuntZone::OnPlayerEnterZone);
	OnActorEndOverlap.AddDynamic(this, &AHuntZone::OnPlayerExitZone);
}

void AHuntZone::OnPlayerEnterZone(AActor* OverlappedActor, AActor* OtherActor)
{

	if (!IsOtherActorThePlayer(OtherActor))
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Player entered hunting zone: Danger Level = %f"), DangerLevel);
	UHuntZoneManager::GetInstance()->AddActiveHuntingZone(this);
	/**
	 * TODO:
	 * 1. Impostare il livello di danger
	 */

}

void AHuntZone::OnPlayerExitZone(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!IsOtherActorThePlayer(OtherActor))
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Player exited hunting zone"));
	UHuntZoneManager::GetInstance()->RemoveActiveHuntingZone(this);
	/**
	 * TODO:
	 * 1. Impostare il livello di danger
	 */
}

bool AHuntZone::IsOtherActorThePlayer(AActor* OtherActor) const
{
	if (OtherActor && OtherActor == this)
	{
		return false;
	}
	OtherActor = Cast<ACharacter>(OtherActor);
	if (!OtherActor)
	{
		return false;
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		return false;
	}
	return OtherActor == PlayerCharacter;
}
