//UBTService_UpdateDistance.cpp
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/UBTService_UpdateDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"

UUBTService_UpdateDistance::UUBTService_UpdateDistance()
{
	NodeName = "UUBTService_UpdateDistance";
	Interval = 0.2f;
	RandomDeviation = 0.0f;
}

void UUBTService_UpdateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();
	
	if (!BB || !AIController)
	{
		return;
	}
	
	APawn* ControlledPawn = AIController->GetPawn();
	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));
	
	if (!ControlledPawn || !TargetActor)
	{
		return;
	}
	
	const float Distance = FVector::Distance(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());
	BB->SetValueAsFloat(DistanceKey.SelectedKeyName, Distance);
}
