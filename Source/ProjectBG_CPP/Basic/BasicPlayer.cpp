// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABasicPlayer::ABasicPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//스프링암 생성 후, 루트에 부착
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	//카메라 생성 후 스프링 암에 부착
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	//메쉬 위치 조정 (캡슐 절반 높이만큼 내려서 발바닥을 바닥에 맞춤)
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90.f, 0)
	);

}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//입력 신호 연결
	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (UIC)
	{

		//BindAction-> 입력 에셋과 실행할 함수를 연결함.
		UIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABasicPlayer::Move);
		UIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABasicPlayer::Look);
		
		//점프는 누를 때 Trigger 시작, 뗄 때 completed 하고 중지 하도록 연결
		UIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABasicPlayer::Jump);
		UIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABasicPlayer::StopJumping);
		UIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &ABasicPlayer::StopJumping);
	}
}
//--------------------------------------------------------------

//카메라 기준 이동 로직(-> 카메라가 보는 방향을 기준으로 앞으로 가도록 계산)
void ABasicPlayer::Move(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>(); //W/S->X, A/D->Y
	
	//카메라 방향으로 바닥을 기준으로 움직이게 설정
	//폰 회전이나 스프링암 회전은 컨트롤러 회전에 따른 정의 따라 회전함.

	//컨트롤러가 현재 어디를 보는지 가져옴
	FRotator CameraRotation = GetControlRotation();

	//바닥에서만 움직여야하므로 고개 숙임/ 기울기 pitch, roll은 0으로 설정. 
	FRotator CameraRotationInFloor = FRotator(0, CameraRotation.Yaw, 0);
	
	//회전값으로부터 앞과 오른쪽 벡터를 추출
	FVector CameraForwardInFloor = UKismetMathLibrary::GetForwardVector(CameraRotationInFloor);
	FVector CameraRightInFloor = UKismetMathLibrary::GetRightVector(CameraRotationInFloor);

	//입력값만큼 이동(X는 앞뒤, Y는 좌우
	AddMovementInput(CameraForwardInFloor* Direction.X);

	AddMovementInput(CameraRightInFloor, Direction.Y); //




}

//-----------------------------------------------------------
//마우스 시선 처리
void ABasicPlayer::Look(const FInputActionValue& Value)
{
	FVector2D RotationDirection = Value.Get<FVector2D>();

	//마우스 상하 이동은 pitch에 , 좌우 이동은 Yaw에 전달해줌. 

	//회전은 playercontroller에 전달 해둠
	AddControllerPitchInput(RotationDirection.Y*-1.f);
	AddControllerYawInput(RotationDirection.X);

	//AddActorLocalRotation(
	//	FRotator(RotationDirection.Y, RotationDirection.X,0) *
	//	UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 360.0f, 0);
}
