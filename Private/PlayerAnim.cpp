// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "LOL/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto ownerPawn = TryGetPawnOwner();
	ATP_ThirdPersonCharacter* player = Cast< ATP_ThirdPersonCharacter>(ownerPawn);
	if (player) {
		//UE_LOG(LogTemp, Warning, TEXT("Move "));

		FVector velocity = player->GetVelocity();

		FVector forwardVector = player->GetActorForwardVector();
		speed = FVector::DotProduct(forwardVector, velocity);

		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

	}
}

void UPlayerAnim::PlayAttackAnim() {
	Montage_Play(attackAnimMontage);
}

void UPlayerAnim::PlayAttackBoomAnim() {
	Montage_Play(attackBoomAnimMontage);
}

void UPlayerAnim::PlayAttackBoomFireAnim() {
	Montage_Play(attackBoomFireAnimMontage);
}