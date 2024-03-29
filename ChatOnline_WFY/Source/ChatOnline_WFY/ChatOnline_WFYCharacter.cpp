// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChatOnline_WFYCharacter.h"

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
#include "UI/Core/UI_CoreMacro.h"
#include "Components/WidgetComponent.h"
#include "../UI/Common/UI_TopTitle.h"

//////////////////////////////////////////////////////////////////////////
// AChatOnline_WFYCharacter

AChatOnline_WFYCharacter::AChatOnline_WFYCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//USkeletalMesh* PlayerMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Kaoru/Meshes/SM_Kaoru"));
	//TSubclassOf<UUI_TopTitle> TopTitlef = LoadClass<UUI_TopTitle>(nullptr, TEXT("/Game/ChatOnline/WFY_Widget/Common/CharacterTopTitle.CharacterTopTitle_C"));
	
	//static ConstructorHelpers::FClassFinder<UUI_TopTitle> TopTitlef(TEXT("/Game/ChatOnline/WFY_Widget/Common/CharacterTopTitle.CharacterTopTitle_C"));

	//UUI_TopTitle* pTopTitle = CreateWidget<UUI_TopTitle>(GetWorld(), TopTitlef.Class);

	//GetMesh()->SetSkeletalMesh(PlayerMesh);

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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	TopTitel = CreateDefaultSubobject<UWidgetComponent>(TEXT("TopTitle"));
	TopTitel->SetupAttachment(RootComponent);
	//TopTitel->SetWidgetClass(TopTitlef);
	//TopTitlef.Get()->
	//TopTitel->GetWidgetClass();
	//TopTitel->SetWidget(pTopTitle);
}

void AChatOnline_WFYCharacter::BeginPlay()
{
	Super::BeginPlay();


	//TopTitel->GetUserWidgetObject();

	//2.初始化配置表
	FSimpleNetGlobalInfo::Get()->Init();//初始化我们通道

	//3.创建对象
	ClientGaming = FSimpleNetManage::CreateManage(ESimpleNetLinkState::LINKSTATE_CONNET, ESimpleSocketType::SIMPLESOCKETTYPE_UDP);
	FSimpleChannel::SimpleControllerDelegate.BindLambda(
		[]()->UClass*
		{
			return UClientObjectController::StaticClass();
		});

	//4.初始化
	if (!ClientGaming->Init())
	{
		ClientGaming = NULL;
		//UE_LOG(LogDBServer, Error, TEXT("Server Init fail."));
		return;
	}
}

void AChatOnline_WFYCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	PlayerNumbers--;

	UE_LOG(LogTemp, Warning, TEXT("UE_LOG:AChatOnline_WFYCharacter::EndPlay::Player:%d"), PlayerNumbers);

	FSimpleNetManage::Destroy(ClientGaming);

	GThread::Get()->Destroy();
}

void AChatOnline_WFYCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GThread::Get()->Tick(DeltaTime);
	ClientGaming->Tick(DeltaTime);
}

FSimpleNetManage* AChatOnline_WFYCharacter::GetClient()
{
	return ClientGaming;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AChatOnline_WFYCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AChatOnline_WFYCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AChatOnline_WFYCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AChatOnline_WFYCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AChatOnline_WFYCharacter::LookUpAtRate);

	// handle touch devices
	//PlayerInputComponent->BindTouch(IE_Pressed, this, &AChatOnline_WFYCharacter::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &AChatOnline_WFYCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AChatOnline_WFYCharacter::OnResetVR);
}




void AChatOnline_WFYCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AChatOnline_WFYCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AChatOnline_WFYCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AChatOnline_WFYCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AChatOnline_WFYCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AChatOnline_WFYCharacter::MoveForward(float Value)
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

void AChatOnline_WFYCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
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
