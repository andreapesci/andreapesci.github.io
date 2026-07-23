void UAbilityIcon::NativeConstruct()
{
	Super::NativeConstruct();

	if (!AbilityImage || !CooldownMaterial)
	{
		return;
	}

	MaterialInstance = UMaterialInstanceDynamic::Create(
		CooldownMaterial,
		this
	);
	if (!MaterialInstance)
	{
		return;
	}

	MaterialInstance->SetTextureParameterValue(
		TEXT("ImageTexture"),
		AbilityTexture
	);
	MaterialInstance->SetScalarParameterValue(TEXT("Progress"), 0.0f);
	AbilityImage->SetBrushFromMaterial(MaterialInstance);
}

void UAbilityIcon::StartCooldown()
{
	if (!MaterialInstance)
	{
		return;
	}

	CooldownElapsed = 0.0f;
	GetWorld()->GetTimerManager().SetTimer(
		CooldownTimer,
		this,
		&UAbilityIcon::UpdateCooldown,
		0.05f,
		true
	);
}

void UAbilityIcon::UpdateCooldown()
{
	CooldownElapsed += 0.05f;
	const float Progress = FMath::Clamp(
		CooldownElapsed / CooldownDuration,
		0.0f,
		1.0f
	);
	MaterialInstance->SetScalarParameterValue(
		TEXT("Progress"),
		1.0f - Progress
	);

	if (Progress >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);
		MaterialInstance->SetScalarParameterValue(TEXT("Progress"), 0.0f);
	}
}
