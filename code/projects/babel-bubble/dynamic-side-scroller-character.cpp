void ADynamicSideScrollerCharacter::OnOrbitReady()
{
	FVector FromCenter = GetActorLocation() - Orbit->Center;
	FromCenter.Z = 0.0f;

	CurrentAngle = FMath::Atan2(FromCenter.Y, FromCenter.X);
	CurrentAngle = FMath::Fmod(
		CurrentAngle + 2.0f * PI,
		2.0f * PI
	);
	bOrbitReady = true;
	UpdateCameraFacing();
}

void ADynamicSideScrollerCharacter::MoveAroundTower(
	const FInputActionValue& Value
)
{
	if (!bOrbitReady || !Orbit)
	{
		return;
	}

	const float Input = Value.Get<float>();
	if (FMath::IsNearlyZero(Input))
	{
		return;
	}

	const float Direction = FMath::Sign(Input);
	CurrentAngle = Orbit->AdvanceAngle(
		CurrentAngle,
		GetWorld()->GetDeltaSeconds(),
		OrbitSpeedDegrees,
		Direction
	);

	const FVector2D Position = Orbit->CalculatePosition(CurrentAngle);
	const FVector Destination(
		Position.X,
		Position.Y,
		GetActorLocation().Z
	);

	AddMovementInput(
		(Destination - GetActorLocation()).GetSafeNormal()
	);
	SetActorRotation(
		Orbit->GetTangentDirection(CurrentAngle, Direction).Rotation()
	);
}

void ADynamicSideScrollerCharacter::UpdateCameraFacing()
{
	FVector ToTower = Orbit->Center - CameraBoom->GetComponentLocation();
	ToTower.Z = 0.0f;
	CameraBoom->SetWorldRotation(ToTower.Rotation());
}
