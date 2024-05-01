#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TechniqueSelectNodeObject.generated.h"

class ABaseAction;
class UImage;

DECLARE_MULTICAST_DELEGATE_TwoParams(FSelectNode, TSubclassOf<ABaseAction>, UImage*);

UCLASS(Blueprintable)
class UE5_DONG_PORT_02_API UTechniqueSelectNodeObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseAction> action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UImage> image;

	FSelectNode DSelectNode;

};
