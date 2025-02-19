// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "HealthInterface.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::LoseHealth(float Amount) {
	Health -= Amount;
	//float damage = 0;
	//damage += Amount;
	//UE_LOG(LogTemp, Warning, TEXT("Health: %f"), damage);
	if (!GetOwner()) {
		UE_LOG(LogTemp, Error, TEXT("Owner xxxxxxxxxxxxxxxxxxxxxxxxxx"));
		return;
	}
	if (GetOwner()->Implements<UHealthInterface>()) {
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
	}


	if (Health <= 0.f){
		Health = 0.f;
		UE_LOG(LogTemp, Warning, TEXT("Die"));

		//UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
		if (GetOwner()->Implements<UHealthComponent>()) {
			IHealthInterface::Execute_OnDeath(GetOwner());
		}

	}
}