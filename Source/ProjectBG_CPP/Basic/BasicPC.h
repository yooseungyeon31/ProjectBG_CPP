// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPC.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTBG_CPP_API ABasicPC : public APlayerController
{
	GENERATED_BODY()

public:

	//입력장치
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<TSoftObjectPtr<UInputMappingContext>> IMC_Basics;
	// .h 헤더 파일의 class 내부 선언
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	//TArray<TSoftObjectPtr<UInputMappingContext>> IMC_Basics;
protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;
};
