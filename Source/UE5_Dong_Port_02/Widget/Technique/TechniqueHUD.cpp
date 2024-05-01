#include "Widget/Technique/TechniqueHUD.h"

#include "TechniqueNodeHUD.h"
#include "TechniqueSelectHUD.h"

#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Widget/Technique/TechniqueNode.h"

void UTechniqueHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTechniqueHUD::SettingTP(uint8 currentTP, uint8 MaxTP)
{
	TB_TP->SetText(FText::FromString(FString::Printf(TEXT("[ %d / %d ]"), currentTP, MaxTP)));
}
