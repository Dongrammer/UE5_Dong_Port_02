#include "Widget/Soul/SoulHUD.h"

#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"

void USoulHUD::SetSouleGage(float MaxGage, float CurrGage)
{
	float Percent = CurrGage / MaxGage;
	PB_SoulGage->SetPercent(Percent);
}
