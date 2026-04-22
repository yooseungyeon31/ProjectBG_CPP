// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"
#include "BasicPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;

UCLASS()
class PROJECTBG_CPP_API ABasicPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//언리얼 엔진에 springarm, camera 기본 설정 넣어주기
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;


	//input 넣어주기
	//이동하기
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;
	//쳐다보기
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;
	//점프하기
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	//input callback
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	//점프는 이미 구현되어있어서 함수 안만들어도 된다.
	//ACharacter 부모 클래스에 이미 Jump()와 StopJumping() 함수가 만들어져 있어 
	// 그대로 가져다 쓰기만 하면 됩니다.
};
