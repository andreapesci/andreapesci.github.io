float UCreatureManager::RandomRangeByDanger(
	const FFloatRange& LowDangerRange,
	const FFloatRange& HighDangerRange
) const
{
	const float Danger = HuntZones->GetCurrentDangerLevel();
	const float Minimum = FMath::Lerp(
		LowDangerRange.GetLowerBoundValue(),
		HighDangerRange.GetLowerBoundValue(),
		Danger
	);
	const float Maximum = FMath::Lerp(
		LowDangerRange.GetUpperBoundValue(),
		HighDangerRange.GetUpperBoundValue(),
		Danger
	);

	return FMath::RandRange(Minimum, Maximum);
}

FVector UCreatureManager::ChooseSpawnLocation()
{
	const float Danger = HuntZones->GetCurrentDangerLevel();
	float MinimumDistance = FMath::Lerp(
		LowDangerMinimumRadius,
		HighDangerMinimumRadius,
		Danger
	);
	float MaximumDistance = FMath::Lerp(
		LowDangerMaximumRadius,
		HighDangerMaximumRadius,
		Danger
	);

	const float SpawnsBeforeCloseRange = FMath::Lerp(
		LowDangerSpawnsBeforeCloseRange,
		HighDangerSpawnsBeforeCloseRange,
		Danger
	);
	const float RepeatPressure = FMath::Clamp(
		RepeatedSpawnsInZone / FMath::Max(SpawnsBeforeCloseRange, 1.0f),
		0.0f,
		1.0f
	);

	MinimumDistance = FMath::Lerp(MinimumDistance, 0.0f, RepeatPressure);
	MaximumDistance = FMath::Lerp(MaximumDistance, 0.0f, RepeatPressure);

	FVector Location = RandomPointInSpawnCone(
		Danger,
		MinimumDistance,
		MaximumDistance
	);
	MoveBehindNearbyCover(Location);
	ProjectToGround(Location);

	return Location;
}

FVector UCreatureManager::RandomPointInSpawnCone(
	float Danger,
	float MinimumDistance,
	float MaximumDistance
) const
{
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector PlayerForward = Player->GetActorForwardVector();

	// At low danger the creature stays behind the player.
	// Higher danger gradually opens the cone to the full circle.
	const float HalfAngle = FMath::Lerp(0.0f, 180.0f, Danger);
	const float Angle = FMath::RandRange(
		180.0f - HalfAngle,
		180.0f + HalfAngle
	);
	const float Distance = FMath::RandRange(
		MinimumDistance,
		MaximumDistance
	);

	const FVector Direction = PlayerForward.RotateAngleAxis(
		Angle,
		FVector::UpVector
	);
	return PlayerLocation + Direction * Distance;
}
