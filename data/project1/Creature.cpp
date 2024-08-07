#include "Creature/Creature.h"

#include "ProjectWinterGameMode.h"
#include "Camera/CameraComponent.h"
#include "Creature/HuntZoneManager.h"

// Sets default values
ACreature::ACreature()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetCollisionProfileName(TEXT("Custom"));
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMeshComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Creature Spawned") );
	UHuntZoneManager* HuntZoneManager = UHuntZoneManager::GetInstance();
	if (HuntZoneManager)
	{
		CurrentDanger = UHuntZoneManager::GetInstance()->GetCurrentDangerLevel();
		HuntZoneManager->OnDangerLevelHasChanged.AddDynamic(this, &ACreature::OnCurrentDangerChange);

	}


}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//todo: convert all this logic in behaviortrees or statetrees?

	if (IsPlayerLookingAtCreature())
	{
		if (TimePlayerLookingAtCreature == 0)
		{
			OnPlayerStartedLookingAtCreature.Broadcast();
		}
		TimePlayerLookingAtCreature += DeltaTime;
		const float TimeToAttackWhenSeen = FMath::Lerp(TimeToAttackWhenSeenLowestDanger, TimeToAttackWhenSeenHighestDanger, CurrentDanger);

		if (TimePlayerLookingAtCreature >= TimeToAttackWhenSeen)
		{
			PerformAttack();
		}
	}
	else
	{
		if (TimePlayerLookingAtCreature != 0)
		{
			OnPlayerStoppedLookingAtCreature.Broadcast();
		}
		TimePlayerLookingAtCreature = 0.0f;
	}

	if (IsPlayerInAttackRange())
	{
		TimePlayerInRange += DeltaTime;
		const float TimeToAttack = FMath::Lerp(TimeToAttackLowestDanger, TimeToAttackHighestDanger, CurrentDanger);
		if (TimePlayerInRange >= TimeToAttack)
		{
			PerformAttack();
		}
	}
	else
	{
		TimePlayerInRange = 0.0f;
	}

}

void ACreature::PerformAttack()
{
	if (!bCreatureHasAttacked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Creature is attacking player!!!") );
		bCreatureHasAttacked = true;
	}

}

bool ACreature::IsPlayerInAttackRange() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	checkf(PlayerController, TEXT("Player controller should be populated."));
	APawn* PlayerPawn = PlayerController->GetPawn();
	checkf(PlayerPawn, TEXT("Player Pawn should be populated."));


	if (PlayerPawn)
	{
		//const float CurrentDangerZoneLevel = UHuntZoneManager::GetInstance()->GetCurrentDangerLevel();
		UE_LOG(LogTemp, Warning, TEXT("CurrentDanger in Creature: %f"), CurrentDanger );
		const float AttackRange = FMath::Lerp(AttackRangeLowestDanger, AttackRangeHighestDanger, CurrentDanger);
		float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());
		return DistanceToPlayer <= AttackRange;
	}

	return false;
}
/*
bool ACreature::IsPlayerLookingAtCreature() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	checkf(PlayerController, TEXT("Player controller should be populated."));
	APawn* PlayerPawn = PlayerController->GetPawn();
	checkf(PlayerPawn, TEXT("Player Pawn should be populated."));

	if (PlayerPawn)
	{
		// Gianni docet
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector PlayerForwardVector = PlayerPawn->GetActorForwardVector();
		FVector DirectionToCreature = GetActorLocation() - PlayerLocation;
		DirectionToCreature.Normalize();
		DrawDebugLine(GetWorld(), PlayerLocation, PlayerForwardVector, FColor::Green, false, 10.0f);
		DrawDebugLine(GetWorld(), PlayerLocation, DirectionToCreature, FColor::Red, false, 10.0f);

		float DotProduct = FVector::DotProduct(PlayerForwardVector, DirectionToCreature);
		float ViewingAngle = FMath::Acos(DotProduct) * (180.0f / PI); // Converti il valore radiante in gradi

		// Consideriamo un angolo di visione di 30 gradi come limite (puoi modificarlo secondo necessità)
		return ViewingAngle <= ViewAngleTriggerEffects;
	}

	return false;
}
*/

bool ACreature::IsPlayerLookingAtCreature() const
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    checkf(PlayerController, TEXT("Player controller should be populated."));
    APawn* PlayerPawn = PlayerController->GetPawn();
    checkf(PlayerPawn, TEXT("Player Pawn should be populated."));

    if (PlayerPawn)
    {
        UCameraComponent* CameraComponent = PlayerPawn->FindComponentByClass<UCameraComponent>();
        if (!CameraComponent)
        {
            UE_LOG(LogTemp, Warning, TEXT("CameraComponent not found."));
            return false;
        }

        FVector PlayerCameraLocation = CameraComponent->GetComponentLocation();
        FVector PlayerCameraForwardVector = CameraComponent->GetForwardVector();
        FVector DirectionToCreature = GetActorLocation() - PlayerCameraLocation;
        DirectionToCreature.Normalize();

        float DistanceToCreature = FVector::Dist(PlayerCameraLocation, GetActorLocation());
        float MinimumDistance = 200.f;

        if (DistanceToCreature < MinimumDistance)
        {
            return true; // Considera la creatura come vista se il giocatore è molto vicino
        }

        float DotProduct = FVector::DotProduct(PlayerCameraForwardVector, DirectionToCreature);
        float ViewingAngle = FMath::Acos(DotProduct) * (180.0f / PI);

        return ViewingAngle <= ViewAngleTriggerEffects;
    }

    return false;
}

void ACreature::OnCurrentDangerChange(float NewDanger)
{
	CurrentDanger = NewDanger;
}
