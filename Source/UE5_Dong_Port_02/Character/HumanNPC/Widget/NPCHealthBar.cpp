#include "Character/HumanNPC/Widget/NPCHealthBar.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/ProgressBar.h"
#include "Animation/WidgetAnimation.h"
#include "Helper.h"

void UNPCHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UNPCHealthBar::SetHealthPercent(float percent)
{
	if (percent > PB_Health->GetPercent())
	{
		PB_Health->SetPercent(percent);
		PB_BackHealth->SetPercent(percent);
		return;
	}
	
	PB_Health->SetPercent(percent);

	amount = (PB_BackHealth->GetPercent() - PB_Health->GetPercent()) / ReductionSoftness;
	GetWorld()->GetTimerManager().SetTimer(backhandle, this, &UNPCHealthBar::SetBackHealthBar, Reductiontime / ReductionSoftness, true, 2.0f);
}

void UNPCHealthBar::SetBackHealthBar()
{
	float prevper = PB_BackHealth->GetPercent();

	PB_BackHealth->SetPercent(prevper - amount);

	if (PB_BackHealth->GetPercent() < PB_Health->GetPercent())
	{
		PB_BackHealth->SetPercent(PB_Health->GetPercent());
		GetWorld()->GetTimerManager().ClearTimer(backhandle);
		return;
	}
}

void UNPCHealthBar::PlayVisibleAnim()
{
	PlayAnimation(VisibleAnim);
}

void UNPCHealthBar::PlayInvisibleAnim()
{
	PlayAnimation(InvisibleAnim);
}
