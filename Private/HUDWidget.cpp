// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "LOL/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "GameFramework/PlayerController.h"
#include "LOLPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized(); // 부모 클래스의 NativeOnInitialized 호출

    // 버튼에 클릭 이벤트 연결
    if (HPButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("HPconnect"));
        HPButton->SetIsEnabled(true);
        HPButton->OnClicked.AddDynamic(this, &UHUDWidget::LevelUptoHP);

    }
    if (SpeedButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("speedconnect"));
        SpeedButton->SetIsEnabled(true);

        SpeedButton->OnClicked.AddDynamic(this, &UHUDWidget::LevelUptoSpeed);
    }
    if (FireSpeedButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("Fireconnect"));
        FireSpeedButton->SetIsEnabled(true);
        FireSpeedButton->OnClicked.AddDynamic(this, &UHUDWidget::LevelUpFiretoSpeed);
    }
    if (!HPButton->OnClicked.IsBound())
    {
        UE_LOG(LogTemp, Error, TEXT("HPButton OnClicked is not bound!"));
    }
    if (!SpeedButton->OnClicked.IsBound())
    {
        UE_LOG(LogTemp, Error, TEXT("SpeedButton OnClicked is not bound!"));
    }
}

void UHUDWidget::LevelUptoHP() {
    UE_LOG(LogTemp, Warning, TEXT("LevelUpHP"));

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
        ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(PlayerController->GetPawn());
        if (Player) {
            Player->LevelUpHP();
            LevelUPEnd();

        }
    }
}

void UHUDWidget::LevelUptoSpeed() {
    UE_LOG(LogTemp, Warning, TEXT("LevelUPSpeed"));

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
        ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(PlayerController->GetPawn());
        if (Player) {
            Player->LevelUpSpeed();
            LevelUPEnd();

        }
    }
}



void UHUDWidget::LevelUpFiretoSpeed() {
    UE_LOG(LogTemp, Warning, TEXT("LevelUpFireSpeed"));

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
        ATP_ThirdPersonCharacter* Player = Cast<ATP_ThirdPersonCharacter>(PlayerController->GetPawn());
        if (Player) {
            Player->LevelUpFireSpeed();
            LevelUPEnd();
        }
    }
}

void UHUDWidget::LevelUPEnd() {
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
        if (ALOLPlayerController* LOLPlayerController = Cast<ALOLPlayerController>(PlayerController)) {
            LOLPlayerController->HideRestartWidget();
        }
    }
}