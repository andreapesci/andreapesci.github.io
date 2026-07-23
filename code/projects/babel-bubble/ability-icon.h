UCLASS()
class UAbilityIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void StartCooldown();

protected:
	virtual void NativeConstruct() override;

private:
	void UpdateCooldown();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AbilityImage;

	UPROPERTY(EditAnywhere, Category = "Ability")
	TObjectPtr<UTexture> AbilityTexture;

	UPROPERTY(EditAnywhere, Category = "Ability")
	TObjectPtr<UMaterialInterface> CooldownMaterial;

	UPROPERTY(EditAnywhere, Category = "Ability", meta = (ClampMin = 0.1))
	float CooldownDuration = 1.0f;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;

	FTimerHandle CooldownTimer;
	float CooldownElapsed = 0.0f;
};
