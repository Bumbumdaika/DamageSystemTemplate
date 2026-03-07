// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageSystemTypes.h"
#include "UObject/Interface.h"
#include "DamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAMAGESYSTEMTEMPLATE_API IDamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	//Добавьте интерфейсные функции в этот класс. Это класс, который будет унаследован для реализации этого интерфейса.
public:
	//В этом месте мы должны реализовать все фукции для классов, которые хотят быть уязвимыми. 
	//UFUCTION в интерфейсах должна иметь значение не только BlueprintCallable, но и BlueprintNativeEvent
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damageable Interface")
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable,  BlueprintNativeEvent, Category = "Damageable Interface")
	float GetMaxHealth();
	
	UFUNCTION(BlueprintCallable,  BlueprintNativeEvent, Category = "Damageable Interface")
	bool GetIsDead();
	
	UFUNCTION(BlueprintCallable,  BlueprintNativeEvent, Category = "Damageable Interface")
	void Health(float HealAmount, AActor* Healer);
	
	UFUNCTION(BlueprintCallable,  BlueprintNativeEvent, Category = "Damageable Interface")
	bool TakeDamage(const FDamageInfo& DamageInfo);
	
};
