#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TechniqueNodeBase.generated.h"

class UTechniqueNodeBase;

USTRUCT(BlueprintType)
struct FRequirements
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<TObjectPtr<UTechniqueNodeBase>, uint8> RequireNode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int RequireCharacterLevel = 1;
};

UCLASS(BlueprintType)
class UE5_DONG_PORT_02_API UTechniqueNodeBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName NodeID = "node_null";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName NodeName = "node_null";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName NodeDescription = "NodeDescription";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 MaxNodeLevel = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRequirements Requirements;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 RequireTP = 1;

};
