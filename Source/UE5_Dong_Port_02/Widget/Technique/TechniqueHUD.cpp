#include "Widget/Technique/TechniqueHUD.h"

#include "TechniqueNodeHUD.h"
#include "TechniqueSelectHUD.h"

#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTechniqueHUD::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate NextHUDPressed, PrevHUDPressed;
	NextHUDPressed.BindUFunction(this, "MoveToNextHUD");
	PrevHUDPressed.BindUFunction(this, "MoveToPrevHUD");
	Bt_NextHUD->OnPressed.Add(NextHUDPressed);
	Bt_PrevHUD->OnPressed.Add(PrevHUDPressed);
}

void UTechniqueHUD::MoveToNextHUD()
{
	UE_LOG(LogTemp, Log, TEXT("MoveToNextHUD Call"));
	this->SetVisibility(ESlateVisibility::Hidden);
	NextHUD->SetVisibility(ESlateVisibility::Visible);
}

void UTechniqueHUD::MoveToPrevHUD()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	PrevHUD->SetVisibility(ESlateVisibility::Visible);
}
