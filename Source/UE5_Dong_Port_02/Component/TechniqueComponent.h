#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Action/ActionData.h"
#include "../Weapon/WeaponData.h"

DECLARE_LOG_CATEGORY_EXTERN(TechniqueComponentLog, Log, All);

#include "TechniqueComponent.generated.h"

class AHero;
class UTechniqueHUDDataAsset;
class UTechniqueHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UTechniqueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTechniqueComponent();

	void ToggleHUD();

	// Select Node in TechniqueNodeHUD
	UFUNCTION()
	void NodeHUDNodeClick(UTechniqueNode* node);	// UFUNCTION은 TObjectPtr 스마트 포인터 사용 불가

	// Select Node in TechniqueSelectHUD
	UFUNCTION()
	void SelectHUDNodeClick(FActionData action, uint8 spaceNum);

protected:
	virtual void BeginPlay() override;

	EWeaponType CurrentWeaponType;
	TObjectPtr<AHero> Player;
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Point")
	uint8 CurrentTP = 100;	// Technique Point
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Point")
	uint8 MaxTP = 100;	// Technique Point

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void MoveToNextHUD();
	UFUNCTION()
	void MoveToPrevHUD();
	UFUNCTION()
	void SetInfoDashNode();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueHUDDataAsset> TechniqueHUDDataAsset;
	UPROPERTY()
	TMap<EWeaponType, TObjectPtr<UTechniqueHUD>> HUDs;
	TObjectPtr<UTechniqueHUD> CurrentHUD;

private:
	TObjectPtr<UTechniqueNode> SelectedNode;
	void NodeSelected(UTechniqueNode* node);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	TArray<FActionData> AvailableAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	TArray<FActionData> SelectedAction;

public:
	UFUNCTION()
	void SelectDashAction(EDashAction dash);
};
