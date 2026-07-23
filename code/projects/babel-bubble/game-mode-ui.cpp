void AGGJProjectGameMode::EnableAbility(EAbility Ability)
{
	UGameHUD* HUD = Cast<UGameHUD>(GameHUD);
	if (!HUD || !HUD->Character)
	{
		return;
	}

	UAbilityIcon* Icon = nullptr;
	FText Tutorial;

	switch (Ability)
	{
	case EAbility::Pow:
		Icon = HUD->PowAbility;
		Tutorial = HUD->PowTutorial;
		if (Icon)
		{
			HUD->Character->OnPlugBubble.AddDynamic(
				Icon,
				&UAbilityIcon::StartCooldown
			);
		}
		break;

	case EAbility::Sturdy:
		Icon = HUD->SturdyAbility;
		Tutorial = HUD->SturdyTutorial;
		if (Icon)
		{
			HUD->Character->OnSolidBubble.AddDynamic(
				Icon,
				&UAbilityIcon::StartCooldown
			);
		}
		break;
	}

	if (!Icon)
	{
		return;
	}

	Icon->SetVisibility(ESlateVisibility::Visible);
	HUD->TutorialText->SetText(Tutorial);
	HUD->TutorialText->SetVisibility(ESlateVisibility::Visible);

	const TWeakObjectPtr<UGameHUD> WeakHUD = HUD;
	FTimerHandle TutorialTimer;
	GetWorld()->GetTimerManager().SetTimer(
		TutorialTimer,
		[WeakHUD]()
		{
			if (UGameHUD* ValidHUD = WeakHUD.Get())
			{
				ValidHUD->TutorialText->SetVisibility(
					ESlateVisibility::Hidden
				);
			}
		},
		HUD->TutorialDuration,
		false
	);
}
