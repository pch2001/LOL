// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyFSM.h"
#include "EnemyAnim.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Fantasy_Pack/Characters/Troll/Mesh/SK_Troll.SK_Troll'"));
	if (tempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("BlockAllDynamic")); // 충돌 프로파일 설정
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true); // 충돌 이벤트 활성화
	GetCapsuleComponent()->SetSimulatePhysics(false);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (GetCapsuleComponent())
	{
		//UE_LOG(LogTemp, Warning, TEXT("CapsuleComponent is valid and initialized."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CapsuleComponent is null!"));
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

