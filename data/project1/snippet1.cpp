// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature/CreatureManager.h"

#include "Components/AudioComponent.h"
#include "Creature/AICreatureController.h"
#include "Creature/HuntZoneManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UCreatureManagerComponent::UCreatureManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	EnvironmentSound = CreateDefaultSubobject<UAudioComponent>(TEXT("EnvironmentSound"));
	EnvironmentSound->bAutoActivate = false;

	HeartBeat = CreateDefaultSubobject<UAudioComponent>(TEXT("HeartBeat"));
	HeartBeat->bAutoActivate = false;
}

void UCreatureManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCreatureManagerComponent::PlayerEnteredHuntingZone()
{
	UE_LOG(LogTemp, Warning, TEXT("Starting spawning logic") );
	StartSpawnLogic();

	if (EnvironmentSound && !EnvironmentSound->IsPlaying())
	{
		EnvironmentSound->FadeIn(1.0f, 1.0f);  // 1 second fade-in with full volume
	}

	if (HeartBeat && !HeartBeat->IsPlaying())
	{
		HeartBeat->FadeIn(1.0f, 1.0f);  // 1 second fade-in with full volume
	}
}

void UCreatureManagerComponent::PlayerLeftHuntingZone()
{
	StopSpawnLogic();

	if (EnvironmentSound && EnvironmentSound->IsPlaying())
	{
		EnvironmentSound->FadeOut(1.0f, 0.0f);  // 1 second fade-out to zero volume
	}

	if (HeartBeat && HeartBeat->IsPlaying())
	{
		HeartBeat->FadeOut(1.0f, 0.0f);  // 1 second fade-out to zero volume
	}

}

void UCreatureManagerComponent::DangerLevelHasChanged(const float& NewDanger) const
{

	if (EnvironmentSound && EnvironmentSound->IsPlaying())
	{
		EnvironmentSound->SetVolumeMultiplier(NewDanger);
		EnvironmentSound->SetPitchMultiplier(NewDanger);
	}

	if (HeartBeat && HeartBeat->IsPlaying())
	{
		float AdjustedVolume = FMath::Lerp(HeartBeatLowestDangerVolume, HeartBeatHighestDangerVolume, NewDanger);
		float AdjustedPitch = FMath::Lerp(HeartBeatLowestDangerRhythm, HeartBeatHighestDangerRhythm, NewDanger);
		HeartBeat->SetVolumeMultiplier(AdjustedVolume);
		HeartBeat->SetPitchMultiplier(AdjustedPitch);
	}



}

void UCreatureManagerComponent::SpawnCreature()
{
	if (SpawnedCreature || !bShouldSpawn)
	{
		return;
	}
	FActorSpawnParameters SpawnParams;
	FVector OutRandomSpawnLocation;
	FRotator OutRandomSpawnRotation;
	CalculateRandomSpawnLocationAndRotation(OutRandomSpawnLocation, OutRandomSpawnRotation);

	SpawnedCreature = GetWorld()->SpawnActor<ACreature>(CreatureClass,OutRandomSpawnLocation, OutRandomSpawnRotation, SpawnParams);
	if (!SpawnedCreature)
	{
		UE_LOG(LogTemp, Error, TEXT("PROBLEMA URGENTE, per qualche motivo la cretura non spawna!!!") );
		return;
	}
	OnCreatureHasSpawned.Broadcast(SpawnedCreature);
	AAICreatureController* AIController = Cast<AAICreatureController>(SpawnedCreature->GetController());
	if (AIController)
	{
		/*
		UBehaviorTree* CreatureBehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/AI/BT_CreatureBehavior.BT_CreatureBehavior"));
		if (CreatureBehaviorTree)
		{
			AIController->RunBehaviorTree(CreatureBehaviorTree);
		}
		*/
	}


	// Schedule despawn

	float OutRandomTimerSpawn;
	CalculateRandomValueInRangeBasedOnDanger(OutRandomTimerSpawn, MinimumDespawnCreatureTimerAtLowestDanger, MaximumDespawnCreatureTimerAtLowestDanger, MinimumDespawnCreatureTimerAtHighestDanger, MaximumDespawnCreatureTimerAtHighestDanger);
	GetWorld()->GetTimerManager().ClearTimer(DespawnTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle, this, &UCreatureManagerComponent::DespawnCreature, OutRandomTimerSpawn, false);
}

void UCreatureManagerComponent::DespawnCreature()
{
	UE_LOG(LogTemp, Warning, TEXT("DespawnCreature") );

	if (!SpawnedCreature)
	{
		return;
	}

	AAICreatureController* AIController = Cast<AAICreatureController>(SpawnedCreature->GetController());
	if (AIController)
	{
		/*
		UBehaviorTree* CreatureBehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/AI/BT_CreatureBehavior.BT_CreatureBehavior"));
		if (CreatureBehaviorTree)
		{
			AIController->RunBehaviorTree(CreatureBehaviorTree);
		}
		*/
	}
	IsCreatureStillInZoneAtDespawn();

	OnCreatureHasDespawned.Broadcast(SpawnedCreature);
	SpawnedCreature->Destroy();
	SpawnedCreature = nullptr;


	// Schedule next spawn
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	if (bShouldSpawn)
	{
		float OutRandomTimerSpawn;
		CalculateRandomValueInRangeBasedOnDanger(OutRandomTimerSpawn, MinimumSpawnCreatureTimerAtLowestDanger, MaximumSpawnCreatureTimerAtLowestDanger, MinimumSpawnCreatureTimerAtHighestDanger, MaximumSpawnCreatureTimerAtHighestDanger);
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UCreatureManagerComponent::SpawnCreature, OutRandomTimerSpawn, false);
	}
}

void UCreatureManagerComponent::StartSpawnLogic()
{
	if (bShouldSpawn)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Starting spawning logic") );
	bShouldSpawn = true;
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	if (SpawnedCreature)
	{
		SpawnedCreature->Destroy();
		SpawnedCreature = nullptr;
	}
	float OutRandomTimerSpawn;
	CalculateRandomValueInRangeBasedOnDanger(OutRandomTimerSpawn, MinimumSpawnCreatureTimerAtLowestDanger, MaximumSpawnCreatureTimerAtLowestDanger, MinimumSpawnCreatureTimerAtHighestDanger, MaximumSpawnCreatureTimerAtHighestDanger);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UCreatureManagerComponent::SpawnCreature, OutRandomTimerSpawn, false);
}

void UCreatureManagerComponent::StopSpawnLogic()
{
	if (!bShouldSpawn)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Stopping spawning logic") );

	bShouldSpawn = false;
}

void UCreatureManagerComponent::CalculateRandomValueInRangeBasedOnDanger(float& OutRandomValue, const float& MinValueLowestEnd, const float& MaxValueLowestEnd, const float& MinValueHighestEnd, const float& MaxValueHighestEnd) const
{
	// Usato interpolazione lineare. Usare metodo dedicato?? float MaxAngle = FMath::Lerp(MinimumSpawnCreatureTimerAtLowestDanger, MinimumSpawnCreatureTimerAtHighestDanger, CurrentDangerZoneLevel);
	const float CurrentDangerZoneLevel = UHuntZoneManager::GetInstance()->GetCurrentDangerLevel();
	const float MinValue = MinValueLowestEnd + (MinValueHighestEnd - MinValueLowestEnd) * CurrentDangerZoneLevel;
	const float MaxValue = MaxValueLowestEnd + (MaxValueHighestEnd - MaxValueLowestEnd) * CurrentDangerZoneLevel;
	OutRandomValue = FMath::RandRange(MinValue, MaxValue);
}

void UCreatureManagerComponent::CalculateRandomSpawnLocationAndRotation(FVector& OutRandomSpawnLocation,
	FRotator& OutRandomSpawnRotation)
{
	ACharacter* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FRotator PlayerRotation = PlayerActor->GetActorRotation();
	FVector PlayerForward = PlayerRotation.Vector();
	const float CurrentDangerZoneLevel = UHuntZoneManager::GetInstance()->GetCurrentDangerLevel();
	float MinimumSpawnDistance = MinimumSpawnCreatureRadiusAtLowestDanger + (MinimumSpawnCreatureRadiusAtHighestDanger - MinimumSpawnCreatureRadiusAtLowestDanger) * CurrentDangerZoneLevel;
	float MaximumSpawnDistance = MaximumSpawnCreatureRadiusAtLowestDanger + (MaximumSpawnCreatureRadiusAtHighestDanger - MaximumSpawnCreatureRadiusAtLowestDanger) * CurrentDangerZoneLevel;
	float EscapeZoneDistance = FMath::Lerp(EscapeZoneRadiusAtLowestDanger, EscapeZoneRadiusAtHighestDanger, CurrentDangerZoneLevel);

	if (SameZoneSpawnsCounter && (SpawnsNeededForVirtualSafeToReachPlayerAtLowestDanger || SpawnsNeededForVirtualSafeToReachPlayerAtHighestDanger))
	{
		float CurrentDecrementLevel = FMath::Lerp(SpawnsNeededForVirtualSafeToReachPlayerAtLowestDanger, SpawnsNeededForVirtualSafeToReachPlayerAtHighestDanger, CurrentDangerZoneLevel);

		if (CurrentDecrementLevel)
		{
			float DecrementByMinimum = (MinimumSpawnDistance / CurrentDecrementLevel) * SameZoneSpawnsCounter;
			float DecrementByMaximum = (MaximumSpawnDistance / CurrentDecrementLevel) * SameZoneSpawnsCounter;

			MinimumSpawnDistance = FMath::Max(0,MinimumSpawnDistance - DecrementByMinimum);
			MaximumSpawnDistance = FMath::Max(0,MaximumSpawnDistance - DecrementByMaximum);


		}

	}
	LastMinimumSpawnLocation = MinimumSpawnDistance;
	//LastMaximumSpawnLocation = MaximumSpawnDistance;
	LastMaximumSpawnLocation = EscapeZoneDistance;



	const float RelativeAngle = FMath::Lerp(0.f, 180.f, CurrentDangerZoneLevel);
	float LeftAngle = 180.0f - RelativeAngle;
	float RightAngle = 180.0f + RelativeAngle;

	FVector LeftDirection = PlayerForward.RotateAngleAxis(LeftAngle, FVector::UpVector);
	FVector RightDirection = PlayerForward.RotateAngleAxis(RightAngle, FVector::UpVector);

	FVector LeftEndPoint = PlayerLocation + LeftDirection * MaximumSpawnDistance;
	FVector RightEndPoint = PlayerLocation + RightDirection * MaximumSpawnDistance;


	OutRandomSpawnLocation = GenerateSpawnLocationInCone(PlayerLocation, PlayerForward, MinimumSpawnDistance, MaximumSpawnDistance, LeftAngle, RightAngle);
	OutRandomSpawnRotation = (PlayerLocation - OutRandomSpawnLocation).Rotation();

	FVector TraceStart = OutRandomSpawnLocation + FVector(0.0f, 0.0f, TraceHeight);
	FVector TraceEnd = OutRandomSpawnLocation - FVector(0.0f, 0.0f, TraceHeight);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	// todo: may need to change this, visibility is not the right one. Will need to maybe set a specific channel for terrain.
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams))
	{
		OutRandomSpawnLocation.Z = HitResult.Location.Z;
		if (DebugTimeDurationInSeconds)
		{
			DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Green, false, 2.0f);
			DrawDebugSphere(GetWorld(), HitResult.Location, 25.0f, 12, FColor::Green, false, 2.0f);
		}
	}
	else
	{
		// Fall back to the player's height if no hit is detected
		OutRandomSpawnLocation.Z = PlayerLocation.Z;
		if (DebugTimeDurationInSeconds)
		{
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
		}
	}

	if (DebugTimeDurationInSeconds)
	{
		DrawDebugLine(GetWorld(), PlayerLocation, LeftEndPoint, FColor::Blue, false, DebugTimeDurationInSeconds, 0, 2.0f);
		DrawDebugLine(GetWorld(), PlayerLocation, RightEndPoint, FColor::Blue, false, DebugTimeDurationInSeconds, 0, 2.0f);
		DrawDebugCircle(GetWorld(), PlayerLocation, MinimumSpawnDistance, 50, FColor::Green, false, DebugTimeDurationInSeconds, 0, 5.0f, FVector(1, 0, 0), FVector(0, 1, 0), false);
		DrawDebugCircle(GetWorld(), PlayerLocation, MaximumSpawnDistance, 50, FColor::Red, false, DebugTimeDurationInSeconds, 0, 5.0f, FVector(1, 0, 0), FVector(0, 1, 0), false);
		DrawDebugCircle(GetWorld(), PlayerLocation, EscapeZoneDistance, 50, FColor::Purple, false, DebugTimeDurationInSeconds, 0, 5.0f, FVector(1, 0, 0), FVector(0, 1, 0), false);
		DrawDebugCircle(GetWorld(), OutRandomSpawnLocation, 10.f, 50, FColor::Purple, false, DebugTimeDurationInSeconds, 0, 5.0f, FVector(1, 0, 0), FVector(0, 1, 0), false);

		FVector DirectionEndPoint = PlayerLocation + PlayerForward * MaximumSpawnDistance;
		DrawDebugLine(GetWorld(), PlayerLocation, DirectionEndPoint, FColor::Yellow, false, DebugTimeDurationInSeconds, 0, 2.0f);
	}

	/*
	float SpawnConeAngle = CurrentDangerZoneLevel * 360.0f;

	float Distance = FMath::FRandRange(MinimumSpawnDistance, MaximumSpawnDistance);
	FVector Direction = PlayerForward.RotateAngleAxis(SpawnConeAngle + 180.0f, FVector::UpVector); // Angolo dietro il giocatore

	RandomSpawnLocation = PlayerLocation + Direction * Distance;


	for (float Angle = -SpawnConeAngle / 2.0f; Angle <= SpawnConeAngle / 2.0f; Angle += 5.0f) // Incrementi di 5 gradi per visualizzazione più densa
	{
		FVector EndPoint = PlayerLocation + Direction * MaximumSpawnDistance;
		DrawDebugLine(GetWorld(), PlayerLocation, EndPoint, FColor::Blue, false, 9.0f, 0, 2.0f);
	}
	FVector EndPoint = PlayerLocation + PlayerForward * MaximumSpawnDistance; // Estendi la linea di 1000 unità
	*/
}

bool UCreatureManagerComponent::IsCreatureStillInZoneAtDespawn()
{
	ACharacter* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = PlayerActor->GetActorLocation();
	FVector CreatureLocation = SpawnedCreature->GetActorLocation();
	float DistanceToPlayer = FVector::Dist(PlayerLocation, CreatureLocation);

	bool bIsInZone = DistanceToPlayer >= LastMinimumSpawnLocation && DistanceToPlayer <= LastMaximumSpawnLocation;



	if (bIsInZone)
	{
		UE_LOG(LogTemp, Log, TEXT("La creatura è ancora nella zona di caccia al momento del despawn."));
		SameZoneSpawnsCounter++;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("La creatura è fuori dalla zona di caccia al momento del despawn."));
		SameZoneSpawnsCounter = 0;
	}
	return bIsInZone;
}

FVector UCreatureManagerComponent::GenerateSpawnLocationInCone(const FVector& PlayerLocation,const FVector& PlayerForward,const float& MinDistance,const float& MaxDistance,const float& LeftAngle,const float& RightAngle)
{
	float RandomDistance = FMath::RandRange(MinDistance, MaxDistance);
	float RandomAngle = FMath::RandRange(LeftAngle, RightAngle);
	FVector SpawnDirection = PlayerForward.RotateAngleAxis(RandomAngle, FVector::UpVector);
	return PlayerLocation + SpawnDirection * RandomDistance;
}
