#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../../Action/ActionData.h"

#include "TechniqueSelectNodeObject.generated.h"

struct FActionData;
class UImage;

DECLARE_MULTICAST_DELEGATE_TwoParams(FSelectNode, FActionData, UImage*);

UCLASS(Blueprintable)
class UE5_DONG_PORT_02_API UTechniqueSelectNodeObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FActionData action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UImage> image;

	FSelectNode DSelectNode;

};
