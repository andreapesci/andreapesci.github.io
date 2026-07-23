// The endpoints remain editable in Unreal so designers can tune the
// heartbeat without changing gameplay code.
UPROPERTY(EditAnywhere, Category = "Winter|Heartbeat|Low Danger")
float LowDangerPitch = 1.0f;

UPROPERTY(EditAnywhere, Category = "Winter|Heartbeat|Low Danger")
float LowDangerVolume = 1.0f;

UPROPERTY(EditAnywhere, Category = "Winter|Heartbeat|High Danger")
float HighDangerPitch = 3.0f;

UPROPERTY(EditAnywhere, Category = "Winter|Heartbeat|High Danger")
float HighDangerVolume = 5.0f;

void UAudioManager::OnPlayerEnteredHuntZone()
{
	UpdateHeartbeatTargets(HuntZones->GetCurrentDangerLevel());

	if (!HeartbeatAudio->IsPlaying())
	{
		CurrentVolume = TargetVolume;
		CurrentPitch = TargetPitch;
		HeartbeatAudio->SetPitchMultiplier(CurrentPitch);
		HeartbeatAudio->FadeIn(FadeDuration, CurrentVolume);
	}
}

void UAudioManager::OnDangerLevelChanged(float Danger)
{
	UpdateHeartbeatTargets(Danger);
}

void UAudioManager::UpdateHeartbeatTargets(float Danger)
{
	TargetVolume = FMath::Lerp(
		LowDangerVolume,
		HighDangerVolume,
		Danger
	);
	TargetPitch = FMath::Lerp(
		LowDangerPitch,
		HighDangerPitch,
		Danger
	);
}

void UAudioManager::UpdateHeartbeat(float DeltaTime)
{
	if (!HeartbeatAudio->IsPlaying())
	{
		return;
	}

	CurrentVolume = FMath::FInterpTo(
		CurrentVolume,
		TargetVolume,
		DeltaTime,
		InterpolationSpeed
	);
	CurrentPitch = FMath::FInterpTo(
		CurrentPitch,
		TargetPitch,
		DeltaTime,
		InterpolationSpeed
	);

	HeartbeatAudio->SetVolumeMultiplier(CurrentVolume);
	HeartbeatAudio->SetPitchMultiplier(CurrentPitch);
}
