#include "Widget/Technique/TechniqueDashHUD.h"

#include "TechniqueDashNode.h"
#include "Action/BaseDash.h"

#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/Image.h"

DEFINE_LOG_CATEGORY(TechniqueDashHUDLog);

void UTechniqueDashHUD::InitHUD(TArray<EDashAction> dashes)
{
	Dashes = dashes;

	if (Dashes.Num() <= 2)
	{
		UE_LOG(LogTemp, Log, TEXT("return : %d"), Dashes.Num());
		return;
	}

	PrevDash = Dashes[Dashes.Num() - 1];
	CurrDash = Dashes[0];
	NextDash = Dashes[1];
	SetImage();
}

void UTechniqueDashHUD::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate next, prev;
	next.BindUFunction(this, "CallNext");
	BT_Next->OnClicked.Add(next);
	prev.BindUFunction(this, "CallPrev");
	BT_Prev->OnClicked.Add(prev);
}

void UTechniqueDashHUD::SetImage()
{
	PrevNode->SetImage(DashImages.FindRef(PrevDash));
	CurrNode->SetImage(DashImages.FindRef(CurrDash));
	NextNode->SetImage(DashImages.FindRef(NextDash));
	SetNodeInfo();
}

void UTechniqueDashHUD::CallNext()
{
	PlayNextAnimation();

	PrevDash = CurrDash;
	CurrDash = NextDash;
	if (NextDash == Dashes[Dashes.Num() - 1])
		NextDash = Dashes[0];
	else
		NextDash = static_cast<EDashAction>(static_cast<uint8>(NextDash) + 1);

	ClickImageVisible(false);
	SetImage();
	DSelectNode.Broadcast(CurrDash);
}

void UTechniqueDashHUD::CallPrev()
{
	PlayPrevAnimation();

	NextDash = CurrDash;
	CurrDash = PrevDash;
	if (PrevDash == Dashes[0])
		PrevDash = Dashes[Dashes.Num() - 1];
	else
		PrevDash = static_cast<EDashAction>(static_cast<uint8>(PrevDash) - 1);

	ClickImageVisible(false);
	SetImage();
	DSelectNode.Broadcast(CurrDash);
}

FNodeInfoData UTechniqueDashHUD::GetNodeInfoData()
{
	FNodeInfoData data;
	data.NodeDescription = CurrNode->NodeDescription;
	data.NodeName = CurrNode->NodeName;

	return data;
}

void UTechniqueDashHUD::ClickImageVisible(bool visible)
{
	if (visible)
		IM_InfoSelected->SetVisibility(ESlateVisibility::HitTestInvisible);
	else
		IM_InfoSelected->SetVisibility(ESlateVisibility::Hidden);
}

/*
void UTechniqueDashHUD::SetNodeInfo()
{
	switch (CurrDash)
	{
	case EDashAction::E_None:
		break;
	case EDashAction::E_GA_Dash_Start:
		break;
	case EDashAction::E_GA_Dash_01:
	{
		CurrNode->NodeDescription = FText::FromString(TEXT("<Speed>0.3��</> ���� <MoveDistance>4M</>�� �̵��մϴ�."));
		CurrNode->NodeName = FText::FromString("�뽬");
		break;
	}
	case EDashAction::E_GA_Dash_02:
	{
		CurrNode->NodeDescription = FText::FromString("<Speed>0.4��</> ���� �⸦ ��� �̵��մϴ�. \n�⸦ ������ ���� ���� ��ȯ�� �����մϴ�. \n Level 1 : <MoveDistance>2M</>�� �̵��մϴ�. \n Level 2 : <MoveDistance>2.5M</>�� �̵��մϴ�.");
		CurrNode->NodeName = FText::FromString("�����뽬");
		break;
	}
	case EDashAction::E_GA_Dash_03:
	{
		CurrNode->NodeDescription = FText::FromString("<Speed>0.8��</> ���� <MoveDistance>4M</>�� �����ϸ� �̵��մϴ�. ���ع��� ���� �� �ֽ��ϴ�.");
		CurrNode->NodeName = FText::FromString("�����뽬");
		break;
	}
	case EDashAction::E_GA_Dash_End:
		break;
	case EDashAction::E_SW_Dash_Start:
		break;
	case EDashAction::E_SW_Dash_01:
	{
		CurrNode->NodeDescription = FText::FromString("///");
		CurrNode->NodeName = FText::FromString("�뽬");
		break;
	}
	case EDashAction::E_SW_Dash_End:
		break;
	case EDashAction::E_Max:
		break;
	default:
		break;
	}
}*/