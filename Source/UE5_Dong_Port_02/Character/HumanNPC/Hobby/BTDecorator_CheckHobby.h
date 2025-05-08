#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckHobby.generated.h"

// �׳� �����庣�̽� ���� �ɵ�?? ���� ��� �Ǵ°� ����
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
