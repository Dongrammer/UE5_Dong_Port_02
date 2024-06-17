#include "Character/HumanNPC.h"

#include "Helper.h"

DEFINE_LOG_CATEGORY(HumanNPCLog);

AHumanNPC::AHumanNPC()
{
	CreateCharacter();
}

void AHumanNPC::BeginPlay()
{
	Super::BeginPlay();
}

void AHumanNPC::CreateCharacter()
{
	Super::CreateCharacter();

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>(L"/Game/Characters/HumanNPC/ABP_HumanNPC"));
}