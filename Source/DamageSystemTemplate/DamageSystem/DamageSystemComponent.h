// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageSystemTypes.h"
#include "Components/ActorComponent.h"
#include "DamageSystemComponent.generated.h"


//Создание событий в компоненте DamageSystemComoponent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, const FDamageInfo&, DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageAvoided, const FDamageInfo&, DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealReceived, float, HealAmount, AActor*, Healer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DAMAGESYSTEMTEMPLATE_API UDamageSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageSystemComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float MaxHealth = 100.f;
private:
	
	UPROPERTY()
	float CurrentHealth = MaxHealth;
	
	UPROPERTY()
	bool IsDead = false;
	UPROPERTY()
	bool IsBlocking = false;
	UPROPERTY()
	bool IsInvincible = false;
	
protected:	
	virtual void BeginPlay() override;
	
		

public:
	
	//void HandleIncomingDamage()
	// Called when the game starts
	UFUNCTION(BlueprintCallable, Category="Damage")
	bool HandleIncomingDamage(const FDamageInfo& DamageInfo);
	
	UFUNCTION(BlueprintCallable, Category="Damage")
	void HandleIncomingHeal(float HealAmount, AActor* Healer);
	
	//Getter functions
	UFUNCTION(BlueprintCallable, BlueprintPure, Category ="Health")
	float GetCurrentHealth(){ return CurrentHealth; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	bool GetIsDead() const { return IsDead; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "States")
	bool GetIsInvincible() const { return IsInvincible; };
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "States")
	bool GetIsBlocking() const { return IsBlocking; };
	
	//Setter Function
	UFUNCTION(BlueprintCallable, Category = "States")
	void SetIsInvincible(bool NewInvicible){ IsInvincible = NewInvicible; };
	
	UFUNCTION(BlueprintCallable, Category = "States")
	void SetIsBlocking(bool NewBlocking){ IsBlocking = NewBlocking; };
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetStartingHealth(float StartingHealth);
	
	
	//DELEGATES
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDamageTaken OnDamageTaken;
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDamageAvoided OnDamageAvoided;
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnHealReceived OnHealReceived;
	
};
