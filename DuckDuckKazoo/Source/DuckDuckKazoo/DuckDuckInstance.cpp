// Fill out your copyright notice in the Description page of Project Settings.


#include "DuckDuckInstance.h"

static const FName SESSION_NAME = FName("MySession");

UDuckDuckInstance::UDuckDuckInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/DuckDuckKazoo/UI/MainMenu/WBP_MainMenu"));
	if (ensure(MenuBPClass.Class != nullptr))
	{
		MainMenu = MenuBPClass.Class;
	}
}

void UDuckDuckInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if (ensure(Subsystem != nullptr))
	{
		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UDuckDuckInstance::OnCreateSessionComplete);
			OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UDuckDuckInstance::OnDestroySessionComplete);
			OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);

			//OnFindSessionCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UDuckDuckInstance::OnFindSessionsComplete);
			//OnFindSessionCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegate);
		}
	}

	/*if (MainMenu && GetWorld())
	{
		UMainMenu* MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenu);
		if (ensure(MainMenuWidget != nullptr))
		{
			MainMenuWidget->SetGameInstance(this);
			MainMenuWidget->AddToViewport();
		}
	}*/
}

void UDuckDuckInstance::CreateASession()
{
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("SessionInterface is invalid in CreateSession."));
		return;
	}

	SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = true;
	SessionSettings->NumPublicConnections = 4;
	SessionSettings->bShouldAdvertise = true;

	UE_LOG(LogTemp, Warning, TEXT("Attempting to create session..."));
	SessionInterface->CreateSession(0, SESSION_NAME, *SessionSettings);
}

void UDuckDuckInstance::SearchAvailableSessions()
{
	if (!ensure(SessionInterface != nullptr)) return;
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UDuckDuckInstance::Host()
{
	if (!SessionInterface.IsValid()) return;

	auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
	if (ExistingSession != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session already exists. Deleting session..."));
		SessionInterface->DestroySession(SESSION_NAME);
		return;
	}
	else
	{
		CreateASession();
	}
}

void UDuckDuckInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session created successfully."));
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create session."));
	}
}

void UDuckDuckInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Previous session destroyed. Creating new one."));
		CreateASession();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to destroy existing session."));
	}
}


void UDuckDuckInstance::Join(const FString& IPAddress) {
	APlayerController* Controller = GetFirstLocalPlayerController();

	if (!ensure(Controller != nullptr)) return;

	Controller->ClientTravel(*IPAddress, ETravelType::TRAVEL_Absolute);
}

/*void UDuckDuckInstance::OpenMenu() {
	if (!ensure(MainMenu != nullptr)) return;

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MainMenu);

	if (!(ensure(Menu != nullptr))) return;

	Menu->SetGameInstance(this);
	Menu->AddToViewport();

	/*
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputMode;

	InputMode.SetWidgetToFocus(MainMenuWidgetClass->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
	*/
//}
