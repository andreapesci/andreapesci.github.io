DECLARE_MULTICAST_DELEGATE(FPlayerStartedLookingAtCreature);
DECLARE_MULTICAST_DELEGATE(FPlayerStoppedLookingAtCreature);
DECLARE_MULTICAST_DELEGATE(FCreatureAttackedPlayer);

UCLASS()
class ACreature : public APawn
{
	GENERATED_BODY()

public:
	FPlayerStartedLookingAtCreature OnPlayerStartedLookingAtCreature;
	FPlayerStoppedLookingAtCreature OnPlayerStoppedLookingAtCreature;
	FCreatureAttackedPlayer OnCreatureAttackedPlayer;

private:
	void UpdateGazePressure(float DeltaTime);
	void UpdateProximityPressure(float DeltaTime);
	bool IsPlayerLookingAtCreature() const;
	bool IsPlayerInAttackRange() const;
	void BeginAttack();

	UPROPERTY(EditAnywhere, Category = "Winter|Combat|Low Danger")
	float LowDangerAttackRange = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Combat|Low Danger")
	float LowDangerAttackDelay = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Combat|Low Danger")
	float LowDangerGazeDelay = 4.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Combat|High Danger")
	float HighDangerAttackRange = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Combat|High Danger")
	float HighDangerAttackDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Combat|High Danger")
	float HighDangerGazeDelay = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Winter|Combat")
	float ViewAngleDegrees = 40.0f;

	UPROPERTY(EditAnywhere, Category = "Winter|Combat")
	float CloseRangeOverride = 200.0f;

	UPROPERTY()
	TObjectPtr<APawn> Player;

	float CurrentDanger = 0.0f;
	float GazeDuration = 0.0f;
	float ProximityDuration = 0.0f;
	bool bPlayerIsLooking = false;
	bool bIsAttacking = false;
};
