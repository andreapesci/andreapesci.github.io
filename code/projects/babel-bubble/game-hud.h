class UAbilityIcon;
class UTextBlock;
class ADynamicSideScrollerCharacter;

UCLASS()
class UGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAbilityIcon> SturdyAbility;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAbilityIcon> PowAbility;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAbilityIcon> BouncyAbility;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TutorialText;

	UPROPERTY(EditAnywhere, Category = "HUD")
	FText PowTutorial;

	UPROPERTY(EditAnywhere, Category = "HUD")
	FText SturdyTutorial;

	UPROPERTY(EditAnywhere, Category = "HUD")
	float TutorialDuration = 2.0f;

	UPROPERTY()
	TObjectPtr<ADynamicSideScrollerCharacter> Character;

protected:
	virtual void NativeConstruct() override;
};
