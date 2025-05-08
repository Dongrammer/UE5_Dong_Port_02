#include "Widget/Battle/DamageFloatingActor.h"
#include "Helper.h"
#include "Components/WidgetComponent.h"
#include "Widget/Battle/DamageFloating.h"

ADamageFloatingActor::ADamageFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	DamageFloatingClass = Helper::GetClass<UDamageFloating>(L"/Game/Widget/Battle/WB_DamageFloating");
	WidgetComponent = Helper::CreateSceneComponent<UWidgetComponent>(this, TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetWidgetClass(DamageFloatingClass);
}

void ADamageFloatingActor::BeginPlay()
{
	Super::BeginPlay();

}

void ADamageFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageFloatingActor::ActiveWidget(float damage)
{

	TObjectPtr<UDamageFloating> damagefloating = Cast<UDamageFloating>(WidgetComponent->GetWidget());
	if (!damagefloating)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADamageFloatingActor : UDamageFloating Casting Fail !!"));
		this->Destroy();
		return;
	}
	damagefloating->FloatingWidget(damage);
	UE_LOG(LogTemp, Log, TEXT("DamageFloatingActor:ActiveWidget"));
	//GetWorld()->GetTimerManager().SetTimerForNextTick([this]() { DestroySelf(); });
	//GetWorld()->GetTimerManager().SetTimerForNextTick(&ADamageFloatingActor::DestroySelf);
	//GetWorld()->GetTimerManager().SetTimerForNextTick();
	FTimerHandle TempHandle;
	GetWorld()->GetTimerManager().SetTimer(TempHandle, [this]() { DestroySelf(); }, 2.0f, false);

	/*FTimerDelegate timerCallback;
	timerCallback.BindLambda([this] { DestroySelf(); });*/
}

void ADamageFloatingActor::DestroySelf()
{
	Destroy();
}

