// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "DamageSystemTemplate/DamageSystem/DamageableCharacterBase.h"

const FName AAIC_EnemyController::TargetActorKeyName(TEXT("TargetActor"));

AAIC_EnemyController::AAIC_EnemyController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 1800.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(2.0f);
	
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectEnemies = false;
	
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	
}

void AAIC_EnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AIPerceptionComponent)
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
			this, 
			&AAIC_EnemyController::OnTargetPerceptionUpdated
			);
	}
}

void AAIC_EnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AAIC_EnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor)
	{
		return;
	}
	
	if (Stimulus.WasSuccessfullySensed())
	{
		SetTargetActor(Actor);
		if (ADamageableCharacterBase* EnemyCharacter = Cast<ADamageableCharacterBase>(GetPawn()))
		{
			EnemyCharacter->SetAIState(EAIState::Angry);
		}
		UE_LOG(LogTemp, Warning, TEXT("AI saw target: %s"), *Actor->GetName());
	}
	else
	{
		AActor* CurrentTarget = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(TargetActorKeyName));
		if (CurrentTarget == Actor)
		{
			ClearTargetActor();
			
			if (ADamageableCharacterBase* EnemyCharacter = Cast<ADamageableCharacterBase>(GetPawn()))
			{
				EnemyCharacter->SetAIState(EAIState::Idle);
			}
		}
	}
	
}

void AAIC_EnemyController::SetTargetActor(AActor* NewTarget)
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsObject(TargetActorKeyName, NewTarget);
	}
}

void AAIC_EnemyController::ClearTargetActor()
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->ClearValue(TargetActorKeyName);
	}
}
