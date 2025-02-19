// Fill out your copyright notice in the Description page of Project Settings.


#include "LOLPlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"

void ALOLPlayerController::BeginPlay() {
	Super::BeginPlay();

}
//void ALOLPlayerController::UpdateHealthPercent(float HealthPercent) {
//	if (HUDWidget != nullptr) {
//		HUDWidget->UpdateHealthPercent(HealthPercent);
//	}
//}

void ALOLPlayerController::ShowHUDWidget() {
	if (BP_HUDWidget != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("oooooooooooooo"));
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void ALOLPlayerController::HideRestartWidget() {
	UE_LOG(LogTemp, Warning, TEXT("xxxxxxxxxxxxxx"));
	HUDWidget->RemoveFromParent();
	HUDWidget->Destruct();
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
	SetPause(false);

}
