class UHuntZoneSubsystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UCreatureManager : public UActorComponent
{
	GENERATED_BODY()

private:
	float RandomRangeByDanger(
		const FFloatRange& LowDangerRange,
		const FFloatRange& HighDangerRange
	) const;
	FVector ChooseSpawnLocation();
	FVector RandomPointInSpawnCone(
		float Danger,
		float MinimumDistance,
		float MaximumDistance
	) const;
	void MoveBehindNearbyCover(FVector& Location) const;
	void ProjectToGround(FVector& Location) const;

	UPROPERTY()
	TObjectPtr<APawn> Player;

	UPROPERTY()
	TObjectPtr<UHuntZoneSubsystem> HuntZones;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn|Low Danger")
	float LowDangerMinimumRadius = 6000.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn|Low Danger")
	float LowDangerMaximumRadius = 8000.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn|High Danger")
	float HighDangerMinimumRadius = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn|High Danger")
	float HighDangerMaximumRadius = 700.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn|Low Danger")
	float LowDangerSpawnsBeforeCloseRange = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Spawn|High Danger")
	float HighDangerSpawnsBeforeCloseRange = 2.0f;

	int32 RepeatedSpawnsInZone = 0;
};
