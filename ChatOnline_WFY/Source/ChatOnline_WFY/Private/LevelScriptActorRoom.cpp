// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScriptActorRoom.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/Engine/TextRenderActor.h"
#include "Kismet/GameplayStatics.h"
#include "LocalTimestampDirectoryVisitor.h"
#include "Engine/Engine.h"
#include "PlatformFilemanager.h"
#include "FileHelper.h"

ALevelScriptActorRoom::ALevelScriptActorRoom()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelScriptActorRoom::BeginPlay() {
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
#if PLATFORM_PS4 || PLATFORM_XBOXONE
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InputComponent->BindAction("Up", IE_Pressed, this, &ALevelScriptActorRoom::OnKeyUp);
	InputComponent->BindAction("Down", IE_Pressed, this, &ALevelScriptActorRoom::OnKeyDown);
	InputComponent->BindAction("Right", IE_Pressed, this, &ALevelScriptActorRoom::OnKeyRight);
	InputComponent->BindAction("Left", IE_Pressed, this, &ALevelScriptActorRoom::OnKeyLeft);
	InputComponent->BindAction("Enter", IE_Pressed, this, &ALevelScriptActorRoom::OnKeyEnter);
	InputComponent->BindAction("Enter", IE_Released, this, &ALevelScriptActorRoom::OnKeyEnterRelease);
#endif
	m_pTestDemoViewController = NewObject<UVoiceControlSystem>();

	bool ret = m_pTestDemoViewController->Create(this);
	if (!ret) {
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("Create view controller failed."));
		return;
	}

	m_pTestDemoViewController->Show(true);
	m_pCurrentViewController = m_pTestDemoViewController;
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.0f, FColor::Yellow, TEXT("BeginPlay"));
	CopyAllAssetsToExternal();
}

void ALevelScriptActorRoom::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	m_pCurrentViewController->UpdateTips();
	m_pCurrentViewController->UpdatePosition();
	ITMGContextGetInstance()->Poll();
}

void ALevelScriptActorRoom::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	ITMGContextGetInstance()->Uninit();
}

void ALevelScriptActorRoom::onChangeDemo() {
}

void ALevelScriptActorRoom::CopyAllAssetsToExternal()
{
	FString formPath = FPaths::ProjectContentDir() + TEXT("StreamingAsset");
#if PLATFORM_IOS
	FString toPath = TEXT("./");
#else
	FString toPath = UTF8_TO_TCHAR(UBaseVoiceControlSystem::getFilePath().c_str());
#endif


	IFileManager* FileManager = &IFileManager::Get();
	TArray<FString> directoriesToIgnoreAndNotRecurse;
	FLocalTimestampDirectoryVisitor Visitor(FPlatformFileManager::Get().GetPlatformFile(), directoriesToIgnoreAndNotRecurse, directoriesToIgnoreAndNotRecurse, false);
	FileManager->IterateDirectory(*formPath, Visitor);

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{

		TArray<uint8> MemFile;
		const FString SourceFilename = TimestampIt.Key();
		if (FFileHelper::LoadFileToArray(MemFile, *SourceFilename))
		{
			FString toFile = toPath + FPaths::GetCleanFilename(*SourceFilename);
			FFileHelper::SaveArrayToFile(MemFile, *toFile);
		}
	}


}

#if PLATFORM_PS4 || PLATFORM_XBOXONE
void ALevelScriptActorRoom::OnKeyUp()
{
	m_pExperientialDemoViewController->OnKeyEvent(EKeyEvent::Up);
}

void ALevelScriptActorRoom::OnKeyDown()
{
	m_pExperientialDemoViewController->OnKeyEvent(EKeyEvent::Down);
}

void ALevelScriptActorRoom::OnKeyRight()
{
	m_pExperientialDemoViewController->OnKeyEvent(EKeyEvent::Right);
}

void ALevelScriptActorRoom::OnKeyLeft()
{
	m_pExperientialDemoViewController->OnKeyEvent(EKeyEvent::Left);
}

void ALevelScriptActorRoom::OnKeyEnter()
{
	m_pExperientialDemoViewController->OnKeyEvent(EKeyEvent::Enter);
}

void ALevelScriptActorRoom::OnKeyEnterRelease()
{
	m_pExperientialDemoViewController->OnKeyEvent(EKeyEvent::EnterRelease);
}
#endif