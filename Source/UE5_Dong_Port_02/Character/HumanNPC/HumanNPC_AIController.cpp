#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

DEFINE_LOG_CATEGORY(HmNPCAIContLog);

AHumanNPC_AIController::AHumanNPC_AIController()
{
	/* ========== Setup Perception System ========== */
	AIPerception = Helper::CreateActorComponent<UAIPerceptionComponent>(this, "AIPerception");
	SetPerceptionComponent(*AIPerception);

	// Sight Config
	SightConfig = Helper::CreateActorComponent<UAISenseConfig_Sight>(this, "SightConfig");
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	// Hearing Config
	HearingConfig = Helper::CreateActorComponent<UAISenseConfig_Hearing>(this, "HearingConfig");
	HearingConfig->HearingRange = 1200.f;
	HearingConfig->SetMaxAge(3.f);

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*HearingConfig);

	AIPerception->OnPerceptionUpdated.AddDynamic(this, &AHumanNPC_AIController::PerceptionUpdate);
}

void AHumanNPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TObjectPtr<AHumanNPC> const npc = Cast<AHumanNPC>(InPawn);

	if (!npc)
	{
		UE_LOG(HmNPCAIContLog, Warning, TEXT("%s : Casting AHumanNPC Fail !!"), *InPawn->GetFName().ToString());
		return;
	}

	TObjectPtr<UBehaviorTree> const tree = npc->GetBehaviorTree();

	if (!tree)
	{
		UE_LOG(HmNPCAIContLog, Warning, TEXT("%s : Get BehaviorTree Fail !!"), *InPawn->GetFName().ToString());
		return;
	}

	UBlackboardComponent* bboard = nullptr;
	UseBlackboard(tree->BlackboardAsset, bboard);
	Blackboard = bboard;
	RunBehaviorTree(tree);
}

void AHumanNPC_AIController::PerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{
	//UE_LOG(LogTemp, Log, TEXT("PerceptionUpdate Call"));
	//for (AActor* updateactor : UpdatedActors)
		//UE_LOG(LogTemp, Log, TEXT("%s"), *updateactor->GetFName().ToString());
}
