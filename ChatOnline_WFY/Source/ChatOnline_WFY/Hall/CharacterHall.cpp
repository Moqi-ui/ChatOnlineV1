// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHall.h"
#include "ThreadManage.h"
#include "Global/SimpleNetGlobalInfo.h"
#include "../Network/ClientObjectController.h"
#include "SimpleNetManage.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "WidgetComponent.h"
#include "../UI/Common/UI_TopTitle.h"

// Sets default values
ACharacterHall::ACharacterHall()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClientHall = NULL;

	//USkeletalMesh* HallMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Kaoru/Meshes/SM_Kaoru_Student"));

	//未能成功记载动画
	//UAnimInstance* AnimIns = LoadObject<UAnimInstance>(nullptr, TEXT("/Game/Kaoru/Anima/AnimaBPkaoru_C"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> HallMesh2(TEXT("/Game/Kaoru/Meshes/SM_Kaoru_Student"));
	
	//加载Widget的方法一
	//static ConstructorHelpers::FClassFinder<UUserWidget> TopTitle2(TEXT("/Game/ChatOnline/WFY_Widget/Common/CharacterTopTitle.CharacterTopTitle_C"));
	//加载Widget的方法二
	//TSubclassOf<UUserWidget>TopTitle = LoadClass<UUserWidget>(this, TEXT("/Game/ChatOnline/WFY_Widget/Common/CharacterTopTitle.CharacterTopTitle_C"));
	//TSubclassOf<UUI_TopTitle> TopTitle = LoadClass<UUI_TopTitle>(this, TEXT("/Game/ChatOnline/WFY_Widget/Common/CharacterTopTitle.CharacterTopTitle_C"));
	//pTopTitle = CreateWidget<UUI_TopTitle>(GetWorld(), TopTitle);
	//这种方法不行
	//UUserWidget* TopTitle3 = LoadObject<UUserWidget>(this, TEXT("/Game/ChatOnline/WFY_Widget/Common/CharacterTopTitle"));

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//GetMesh()->SetSkeletalMesh(HallMesh);
	//GetMesh()->SetAnimClass(AnimIns->StaticClass());
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	ShowWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ShowWidget"));
	ShowWidget->SetupAttachment(RootComponent);
	//ShowWidget->SetWidgetClass(TopTitle);
	//ShowWidget->SetWidget(pTopTitle);
	//ShowWidget->SetTwoSided(true);
	//ShowWidget->SetWidgetClass(TopTitle2.Class);
}

FSimpleNetManage* ACharacterHall::GetClient()
{

	return ClientHall;
}
// Called when the game starts or when spawned
void ACharacterHall::BeginPlay()
{
	Super::BeginPlay();

	//TopTitle->SetTextTitle("dfdss");
	//pTopTitle->SetTitle("myname");

	//ShowWidget->SetWidget(pTopTitle);
	//2.初始化配置表
	FSimpleNetGlobalInfo::Get()->Init();//初始化我们通道

	//3.创建对象
	ClientHall = FSimpleNetManage::CreateManage(ESimpleNetLinkState::LINKSTATE_CONNET, ESimpleSocketType::SIMPLESOCKETTYPE_UDP);
	FSimpleChannel::SimpleControllerDelegate.BindLambda(
		[]()->UClass*
		{
			return UClientObjectController::StaticClass();
		});

	//4.初始化
	if (!ClientHall->Init())
	{
		ClientHall = NULL;
		//UE_LOG(LogDBServer, Error, TEXT("Server Init fail."));
		return;
	}
	
}

void ACharacterHall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);



	FSimpleNetManage::Destroy(ClientHall);
	GThread::Get()->Destroy();

}

// Called every frame
void ACharacterHall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GThread::Get()->Tick(DeltaTime);
	ClientHall->Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterHall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterHall::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterHall::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACharacterHall::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacterHall::LookUpAtRate);

	// handle touch devices
	//PlayerInputComponent->BindTouch(IE_Pressed, this, &ACharacterHall::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &ACharacterHall::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACharacterHall::OnResetVR);


}


void ACharacterHall::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACharacterHall::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ACharacterHall::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ACharacterHall::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACharacterHall::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACharacterHall::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACharacterHall::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
