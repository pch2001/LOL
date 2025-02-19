// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void LevelUptoSpeed();
	UFUNCTION()
	void LevelUptoHP();
	UFUNCTION()
	void LevelUpFiretoSpeed();
	UFUNCTION()
	void LevelUPEnd();

	            
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SpeedButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* HPButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* FireSpeedButton;





};
