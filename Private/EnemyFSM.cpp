// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "LOL/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "LOL.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAnim.h"
#include "HealthComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATP_ThirdPersonCharacter::StaticClass());
	target = Cast<ATP_ThirdPersonCharacter>(actor);
	me = Cast<AEnemy>(GetOwner());

	anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());
	
	ai = Cast<AAIController>(me->GetController());
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}

}

// 166페이지

void UEnemyFSM::IdleState() {
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime) {
		mState = EEnemyState::Move;
		currentTime = 0;
		anim->animState = mState;

	}
}

void UEnemyFSM::MoveState() {
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal()*0.2f);
	if (ai && ai->GetCharacter())
	{
		ai->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200.0f; // 속도 설정
	}
	ai->MoveToLocation(destination);
	
	if (dir.Size() < attackRange) {

		mState = EEnemyState::Attack;

		anim->animState = mState;
		currentTime = attackDelayTime;
	}
}

void UEnemyFSM::AttackState() {
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime) {
		//UE_LOG(LogTemp, Warning, TEXT("Attack!!!"));
		currentTime = 0;
		anim->bAttackPlay = true;

		if (target) {
			ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(target);
			if (Player) { // 캐스팅 성공 시
				UHealthComponent* healthComponent = Player->FindComponentByClass<UHealthComponent>();
				if (healthComponent!=nullptr) {
					//UE_LOG(LogTemp, Warning, TEXT("Attack!!!"));

					//healthComponent->LoseHealth(Damage);
				}
			}
		}

	}

	if (target) { // target이 nullptr인지 다시 확인
		float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
		if (distance > attackRange) {
			mState = EEnemyState::Move;
			anim->animState = mState;
		}
	}
	
}
void UEnemyFSM::DamageState() {
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > 0.5f) {
		mState = EEnemyState::Idle;
		currentTime = 0;
		anim->animState = mState;
	}
}

void UEnemyFSM::DieState() {
	if (anim->bDieDone == false) {
		return;
	}
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	me->SetActorLocation(P);
	if (P.Z < 1150.0f) {
		ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(target);
		Player->expUP();
		//UE_LOG(LogTemp, Log, TEXT("EXP : %d"), Player->exp);
		me->Destroy();

	}

}

void UEnemyFSM::OnDamageProcess(float power) {
	//me->Destroy();
	hp-=power;
	if (hp > 0) {
		mState = EEnemyState::Damage;
		anim->PlayDamageAnim(FName("Damage0"));

	}
	else {
		mState = EEnemyState::Die;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		anim->PlayDamageAnim(TEXT("Die"));
		

	}
	anim->animState = mState;
}