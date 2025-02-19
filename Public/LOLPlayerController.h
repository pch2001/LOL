// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LOLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ALOLPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<class URestartWidget> BP_RestartWidget;

	void ShowHUDWidget();
	void HideRestartWidget();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

	//void UpdateHealthPercent(float HealthPercent);
protected:
	virtual void BeginPlay() override;

private:
	/*UPROPERTY()
	class URestartWidget* RestartWidget;*/

	UPROPERTY()
	class UHUDWidget* HUDWidget;
	
};
