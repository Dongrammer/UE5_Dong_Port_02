#include "Widget/Battle/DamageFloating.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UDamageFloating::NativeConstruct()
{
	Super::NativeConstruct();

	//if (AN_Floating)
	//{
	//	DFinishEvent.BindDynamic(this, &UDamageFloating::DestroythisWidget);
	//	//BindToAnimationFinished(AN_Floating, FWidgetAnimationDynamicEvent::BindUFunction(this, TEXT("DestroyWidget")));
	//	//BindToAnimationFinished(AN_Floating, this, &UDamageFloating::DestroythisWidget);
	//	BindToAnimationFinished(AN_Floating, DFinishEvent);
	//}
}

void UDamageFloating::FloatingWidget(int damage)
{
	TB_Damage->SetText(FText::FromString(FString::Printf(TEXT("%d"), damage)));
	PlayAnimation(AN_Floating);
}

void UDamageFloating::DestroythisWidget()
{
	/*RemoveFromParent();
	this->ConditionalBeginDestroy();*/
}
