UCLASS()
class ADynamicSideScrollerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	void MoveAroundTower(const FInputActionValue& Value);
	void UpdateCameraFacing();
	void OnOrbitReady();

	UPROPERTY()
	TObjectPtr<USuperellipseOrbitComponent> Orbit;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float OrbitSpeedDegrees = 90.0f;

	float CurrentAngle = 0.0f;
	bool bOrbitReady = false;
};
