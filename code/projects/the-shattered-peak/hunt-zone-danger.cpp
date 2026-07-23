void UHuntZoneSubsystem::AddHuntZone(AHuntZone* Zone)
{
	if (!IsValid(Zone) || ActiveZones.Contains(Zone))
	{
		return;
	}

	const bool WasOutside = ActiveZones.IsEmpty();
	ActiveZones.Add(Zone);
	RecalculateDanger();

	if (WasOutside && !bZonesSuppressed)
	{
		OnPlayerEnteredHuntZone.Broadcast();
	}
}

void UHuntZoneSubsystem::RemoveHuntZone(AHuntZone* Zone)
{
	if (ActiveZones.Remove(Zone) == 0)
	{
		return;
	}

	RecalculateDanger();

	if (ActiveZones.IsEmpty() && !bZonesSuppressed)
	{
		OnPlayerLeftHuntZone.Broadcast();
	}
}

void UHuntZoneSubsystem::RecalculateDanger()
{
	float NewDanger = 0.0f;

	for (const AHuntZone* Zone : ActiveZones)
	{
		if (IsValid(Zone))
		{
			NewDanger = FMath::Max(NewDanger, Zone->GetDangerLevel());
		}
	}

	NewDanger = FMath::Clamp(NewDanger, 0.0f, 1.0f);
	if (FMath::IsNearlyEqual(NewDanger, CurrentDanger))
	{
		return;
	}

	CurrentDanger = NewDanger;
	OnDangerLevelChanged.Broadcast(CurrentDanger);
}

void UHuntZoneSubsystem::SuppressDangerFor(float Duration)
{
	if (Duration <= 0.0f)
	{
		return;
	}

	bZonesSuppressed = true;
	CurrentDanger = 0.0f;
	OnDangerLevelChanged.Broadcast(CurrentDanger);
	OnPlayerLeftHuntZone.Broadcast();

	GetWorld()->GetTimerManager().SetTimer(
		ReactivationTimer,
		this,
		&UHuntZoneSubsystem::ReactivateZones,
		Duration,
		false
	);
}
