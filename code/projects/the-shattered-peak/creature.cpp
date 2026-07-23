void ACreature::UpdateGazePressure(float DeltaTime)
{
	if (!IsPlayerLookingAtCreature())
	{
		if (bPlayerIsLooking)
		{
			OnPlayerStoppedLookingAtCreature.Broadcast();
		}

		bPlayerIsLooking = false;
		GazeDuration = 0.0f;
		return;
	}

	if (!bPlayerIsLooking)
	{
		bPlayerIsLooking = true;
		OnPlayerStartedLookingAtCreature.Broadcast();
	}

	GazeDuration += DeltaTime;
	const float DelayBeforeAttack = FMath::Lerp(
		LowDangerGazeDelay,
		HighDangerGazeDelay,
		CurrentDanger
	);

	if (GazeDuration >= DelayBeforeAttack)
	{
		BeginAttack();
	}
}

void ACreature::UpdateProximityPressure(float DeltaTime)
{
	if (!IsPlayerInAttackRange())
	{
		ProximityDuration = 0.0f;
		return;
	}

	ProximityDuration += DeltaTime;
	const float DelayBeforeAttack = FMath::Lerp(
		LowDangerAttackDelay,
		HighDangerAttackDelay,
		CurrentDanger
	);

	if (ProximityDuration >= DelayBeforeAttack)
	{
		BeginAttack();
	}
}

bool ACreature::IsPlayerLookingAtCreature() const
{
	const UCameraComponent* Camera =
		Player->FindComponentByClass<UCameraComponent>();
	if (!Camera)
	{
		return false;
	}

	const FVector ToCreature =
		(GetActorLocation() - Camera->GetComponentLocation()).GetSafeNormal();
	const float Distance = FVector::Distance(
		Camera->GetComponentLocation(),
		GetActorLocation()
	);

	if (Distance <= CloseRangeOverride)
	{
		return true;
	}

	const float Alignment = FVector::DotProduct(
		Camera->GetForwardVector(),
		ToCreature
	);
	const float MinimumAlignment = FMath::Cos(
		FMath::DegreesToRadians(ViewAngleDegrees)
	);

	return Alignment >= MinimumAlignment;
}

bool ACreature::IsPlayerInAttackRange() const
{
	const float AttackRange = FMath::Lerp(
		LowDangerAttackRange,
		HighDangerAttackRange,
		CurrentDanger
	);
	return FVector::Distance(
		GetActorLocation(),
		Player->GetActorLocation()
	) <= AttackRange;
}

void ACreature::BeginAttack()
{
	if (bIsAttacking)
	{
		return;
	}

	bIsAttacking = true;
	OnCreatureAttackedPlayer.Broadcast();
}
