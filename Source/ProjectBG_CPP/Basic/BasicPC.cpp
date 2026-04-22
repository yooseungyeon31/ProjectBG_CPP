// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPC.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ABasicPC::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn); //부모 클래스이 기본 동작 수행


    if (IsLocalPlayerController())
    {
        //향상된 입력 서브시스템 가져오기
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

        if (Subsystem)
        {
            //혹시 남아있을지 모르는 기존 매핑 정보 취소
            Subsystem->ClearAllMappings();
            //배열에 담긴 조작 설정들을 하니씩 적용
            for (const auto& IMC : IMC_Basics)
            {
                Subsystem->AddMappingContext(IMC.LoadSynchronous(), 0);
            }
        }
    }
}

void ABasicPC::OnUnPossess()
{
    Super::OnUnPossess();

    if (IsLocalPlayerController())
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

        if (Subsystem)
        {
            //더이상 조종하지 않으면 조작법 제거
            Subsystem->ClearAllMappings();
        }
    }
}