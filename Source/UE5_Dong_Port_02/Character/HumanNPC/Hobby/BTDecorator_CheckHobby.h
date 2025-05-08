#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckHobby.generated.h"

// 그냥 블랙보드베이스 쓰면 될듯?? 굳이 없어도 되는것 같음
enum class EHobbies : uint8;

UCLASS()
class UE5_DONG_PORT_02_API UBTDecorator_CheckHobby : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

protected:
	UBTDecorator_CheckHobby();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EHobbies checkNPCHobby;
};
