FVector2D USuperellipseOrbitComponent::CalculatePosition(float Angle) const
{
	const float Cosine = FMath::Cos(Angle);
	const float Sine = FMath::Sin(Angle);
	const float Exponent = FMath::Max(SuperellipseExponent, 0.1f);
	const float Radius = FMath::Pow(
		FMath::Pow(FMath::Abs(Cosine), Exponent) +
			FMath::Pow(FMath::Abs(Sine), Exponent),
		-1.0f / Exponent
	);

	return FVector2D(
		Center.X + (TowerExtent.X + DistanceFromTower) * Radius * Cosine,
		Center.Y + (TowerExtent.Y + DistanceFromTower) * Radius * Sine
	);
}

float USuperellipseOrbitComponent::AdvanceAngle(
	float CurrentAngle,
	float DeltaTime,
	float Speed,
	float Direction
) const
{
	CurrentAngle += FMath::DegreesToRadians(Speed) *
		DeltaTime *
		Direction;

	return FMath::Fmod(CurrentAngle + 2.0f * PI, 2.0f * PI);
}

FVector USuperellipseOrbitComponent::GetTangentDirection(
	float Angle,
	float Direction
) const
{
	return FVector(
		-FMath::Sin(Angle) * Direction,
		FMath::Cos(Angle) * Direction,
		0.0f
	).GetSafeNormal();
}
