// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION()
	void OnRestartClicked();

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	virtual void NativeOnInitialized() override;
	
};
