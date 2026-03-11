//DamageableCharacterBase.h
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableInterface.h"
#include "GameFramework/Character.h"
#include "DamageableCharacterBase.generated.h"

//Forward Declaration
UENUM(BlueprintType)
enum EAIState
{
	None UMETA(DisplayName="None"),
	Idle UMETA(DisplayName = "Idle"),
	Angry UMETA(DisplayName = "Patrol"),
	
};

class UDamageSystemComponent;

UCLASS()
class DAMAGESYSTEMTEMPLATE_API ADamageableCharacterBase : public ACharacter, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADamageableCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Объявление событий из компонента в персонаже. 
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamageTaken(const FDamageInfo& DamageInfo);
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamageAvoided(const FDamageInfo& DamageInfo);
	UFUNCTION(BlueprintNativeEvent)
	void RespondToHealReceived(const FDamageInfo& DamageInfo);
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDeath();
	
	//AI
	EAIState AIState = EAIState::Idle;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Damageable Interface Implementations
	//Это функция из интерфейса которую надо переопределить, поэтому в ней не нужен макрос UFUNCTION
	virtual float GetMaxHealth_Implementation() override;
	virtual float GetCurrentHealth_Implementation() override;
	virtual bool GetIsDead_Implementation() override;
	virtual void Health_Implementation(float HealAmount, AActor* Healer) override;
	virtual bool TakeDamage_Implementation(const FDamageInfo& DamageInfo) override;
	
	UFUNCTION(BlueprintCallable)
	void SetAIState(EAIState NewState);
	
	//AI
	UFUNCTION(BlueprintPure)
	EAIState GetAIState() const {return AIState;}
	
	//Damage System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDamageSystemComponent> DamageSystemComponent;
};
