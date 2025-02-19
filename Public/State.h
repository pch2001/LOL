// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "State.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API UState : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* hpText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* speedText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* firespeedText;
};
