// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableCharacterBase.h"
#include "DamageSystemComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ADamageableCharacterBase::ADamageableCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DamageSystemComponent=CreateDefaultSubobject<UDamageSystemComponent>(TEXT("Damage System Component"));
}

void ADamageableCharacterBase::SetAIState(EAIState NewState)
{
	AIState = NewState;
}


// Called when the game starts or when spawned
void ADamageableCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (DamageSystemComponent)
	{
		//Диспетчеры событий на C++(DamageSystemComponent их реализация)
		DamageSystemComponent->OnDamageTaken.AddDynamic(this, &ADamageableCharacterBase::RespondToDamageTaken);
		DamageSystemComponent->OnDamageAvoided.AddDynamic(this, &ADamageableCharacterBase::RespondToDamageAvoided);
		DamageSystemComponent->OnHealReceived.AddDynamic(this, &ADamageableCharacterBase::Health_Implementation);
		DamageSystemComponent->OnDeath.AddDynamic(this, &ADamageableCharacterBase::RespondToDeath);
	}
}

void ADamageableCharacterBase::RespondToDamageTaken_Implementation(const FDamageInfo& DamageInfo)
{
}

void ADamageableCharacterBase::RespondToDamageAvoided_Implementation(const FDamageInfo& DamageInfo)
{
}

void ADamageableCharacterBase::RespondToHealReceived_Implementation(const FDamageInfo& DamageInfo)
{
}

// СОздание смерти. 
void ADamageableCharacterBase::RespondToDeath_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	
}

// Called every frame
void ADamageableCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADamageableCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ADamageableCharacterBase::GetMaxHealth_Implementation()
{
	//Возвращает максимальное количество из переменной MaxHealth из DamageSystemComponent
	if (!DamageSystemComponent){return 0.f;}
	return IDamageableInterface::GetMaxHealth_Implementation();
}

float ADamageableCharacterBase::GetCurrentHealth_Implementation()
{
	if (!DamageSystemComponent){return 0.f;}
	return IDamageableInterface::GetCurrentHealth_Implementation();
}

bool ADamageableCharacterBase::GetIsDead_Implementation()
{
	if (!DamageSystemComponent){return false;}
	return IDamageableInterface::GetIsDead_Implementation();
}

void ADamageableCharacterBase::Health_Implementation(float HealAmount, AActor* Healer)
{
	if (DamageSystemComponent)
	{
		DamageSystemComponent->HandleIncomingHeal(HealAmount,  Healer);
	}
	
}

bool ADamageableCharacterBase::TakeDamage_Implementation(const FDamageInfo& DamageInfo)
{
	if (!DamageSystemComponent){return false;}
	return DamageSystemComponent->HandleIncomingDamage(DamageInfo);
	
}

