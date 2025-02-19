// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;

	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
	class UAnimMontage* attackAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
	class UAnimMontage* attackBoomAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
	class UAnimMontage* attackBoomFireAnimMontage;


	void PlayAttackAnim();

	void PlayAttackBoomAnim();
	void PlayAttackBoomFireAnim();


	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	
};
