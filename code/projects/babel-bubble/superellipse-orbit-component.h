DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOrbitInitialized);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USuperellipseOrbitComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FVector2D CalculatePosition(float Angle) const;
	float AdvanceAngle(
		float CurrentAngle,
		float DeltaTime,
		float Speed,
		float Direction
	) const;
	FVector GetTangentDirection(float Angle, float Direction) const;

	UPROPERTY(EditAnywhere, Category = "Orbit")
	float DistanceFromTower = 200.0f;

	UPROPERTY(
		EditAnywhere,
		Category = "Orbit",
		meta = (ClampMin = "0.1")
	)
	float SuperellipseExponent = 4.0f;

	UPROPERTY(BlueprintAssignable)
	FOrbitInitialized OnOrbitInitialized;

	FVector Center = FVector::ZeroVector;
	FVector2D TowerExtent = FVector2D::ZeroVector;
};
