//AIC_EnemyController.h
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIC_EnemyController.generated.h"

/**
 * 
 */
//Forward Decloration
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class DAMAGESYSTEMTEMPLATE_API AAIC_EnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	//Конструктор
	AAIC_EnemyController();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override; // событие одержимости ИИ
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AI)
	UBehaviorTree* BehaviorTree;
	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	void SetTargetActor(AActor* NewTarget);
	void ClearTargetActor();
	
	static const FName TargetActorKeyName;
	
};
