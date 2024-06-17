#include "Widget/Technique/TechniqueDashNode.h"

#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
//#include "Components/Button.h"

void UTechniqueDashNode::SetImage(TObjectPtr<UTexture2D> texture)
{
	if (!texture)
	{
		UE_LOG(LogTemp, Warning, TEXT("TechniqueDashNode : SetImage texture Is NULL !!"));
		return;
	}

	FTextureParameterValue temp;
	temp.ParameterValue = texture;
	IM_Base->GetDynamicMaterial()->SetTextureParameterValue("Texture", texture);
}