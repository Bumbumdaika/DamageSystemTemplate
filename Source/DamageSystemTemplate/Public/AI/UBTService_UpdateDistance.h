//UBTService_UpdateDistance.h
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UBTService_UpdateDistance.generated.h"

/**
 * 
 */
UCLASS()
class DAMAGESYSTEMTEMPLATE_API UUBTService_UpdateDistance : public UBTService
{
	GENERATED_BODY()
	
public:
	UUBTService_UpdateDistance();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DistanceKey;
	
};
