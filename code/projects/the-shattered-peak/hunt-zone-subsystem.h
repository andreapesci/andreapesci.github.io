DECLARE_MULTICAST_DELEGATE(FPlayerEnteredHuntZone);
DECLARE_MULTICAST_DELEGATE(FPlayerLeftHuntZone);
DECLARE_MULTICAST_DELEGATE_OneParam(
	FDangerLevelChanged,
	const float& /* NewDanger */
);

class AHuntZone;

UCLASS()
class UHuntZoneSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void AddHuntZone(AHuntZone* Zone);
	void RemoveHuntZone(AHuntZone* Zone);
	void SuppressDangerFor(float Duration);

	float GetCurrentDangerLevel() const;
	bool IsPlayerInsideHuntZone() const;

	FPlayerEnteredHuntZone OnPlayerEnteredHuntZone;
	FPlayerLeftHuntZone OnPlayerLeftHuntZone;
	FDangerLevelChanged OnDangerLevelChanged;

private:
	void RecalculateDanger();
	void ReactivateZones();

	TArray<TObjectPtr<AHuntZone>> ActiveZones;
	float CurrentDanger = 0.0f;
	bool bZonesSuppressed = false;
	FTimerHandle ReactivationTimer;
};
