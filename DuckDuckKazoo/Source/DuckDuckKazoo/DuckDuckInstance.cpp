// Fill out your copyright notice in the Description page of Project Settings.


#include "DuckDuckInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainMenu.h"

static const FName SESSION_NAME = FName("MySession");
static const FName SERVER_NAME_SETTINGS_KEY = FName("ServerName");

UDuckDuckInstance::UDuckDuckInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/DuckDuckKazoo/UI/MainMenu/WBP_MainMenu"));
	if (ensure(MenuBPClass.Class != nullptr))
	{
		MainMenu = MenuBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> 
}

void UDuckDuckInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();

	if (OSS)
	{
		SessionInterface = OSS->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("SessionInterface is valid"));
			OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UDuckDuckInstance::OnCreateSessionComplete);
			OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UDuckDuckInstance::OnDestroySessionComplete);
			OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);

			OnFindSessionCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UDuckDuckInstance::OnFindSessionsComplete);
			OnFindSessionCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegate);
		
			OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UDuckDuckInstance::OnJoinSessionComplete);
			OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
		}
	}

	if (MainMenu && GetWorld())
	{
		UMainMenu* MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenu);
		if (ensure(MainMenuWidget != nullptr))
		{
			MainMenuWidget->SetGameInstance(this);
			MainMenuWidget->AddToViewport();
		}
	}
}

void UDuckDuckInstance::Shutdown()
{
	Super::Shutdown();
	if (SessionInterface.IsValid())
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle); // If you add this delegate
	}
}

// Open menu
void UDuckDuckInstance::OpenMenu() {
	if (!ensure(MainMenu != nullptr)) return;

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MainMenu);

	if (!(ensure(Menu != nullptr))) return;

	Menu->SetGameInstance(this);
	Menu->AddToViewport();
}

// Singleplayer logic
void UDuckDuckInstance::StartSingleplayerMode(FName MapName)
{
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
}

// Quit logic
void UDuckDuckInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(),0),EQuitPreference::Quit, true);
}


// Local multiplayer logic
void UDuckDuckInstance::HostLocally()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/DuckDuckKazoo/Levels/Lobby?listen");
	}
}

void UDuckDuckInstance::JoinLocally(const FString& IPAddress) {
	APlayerController* Controller = GetFirstLocalPlayerController();

	if (!ensure(Controller != nullptr)) return;

	Controller->ClientTravel(*IPAddress, ETravelType::TRAVEL_Absolute);
}

void UDuckDuckInstance::LaunchGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/DuckDuckKazoo/Levels/MainMap?listen");
	}
}

// Online subsystem host methods
void UDuckDuckInstance::HostOnline()
{
	if (!SessionInterface.IsValid()) return;

	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
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

void UDuckDuckInstance::CreateASession()
{
	if (!SessionInterface.IsValid()) return;

	SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = false;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bUseLobbiesIfAvailable = true;

	/*SessionSettings->bIsLANMatch = true;
	SessionSettings->NumPublicConnections = 4;
	SessionSettings->bShouldAdvertise = true;*/

	SessionInterface->CreateSession(0, SESSION_NAME, *SessionSettings);
}

void UDuckDuckInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session created successfully"));
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/DuckDuckKazoo/Levels/Lobby?listen");
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session creation failed"));
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

// Online Subsystem join methods
void UDuckDuckInstance::SearchAvailableSessions()
{
	if (!SessionInterface.IsValid()) return;
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = false;
		SessionSearch->MaxSearchResults = 100;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UDuckDuckInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);

	TArray<FServerData> ServerData = TArray<FServerData>();

	if (bWasSuccessful && SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			FServerData Data;
			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
			Data.HostName = SearchResult.Session.OwningUserName;
			FString ServerHostName;

			if (SearchResult.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerHostName))
			{
				Data.Name = ServerHostName;
			}
			else
			{
				Data.Name = "Couldn't find name";
			}
			ServerData.Add(Data);
		}
	}
	//notifyListeners(ServerData);
}

/*void UDuckDuckInstance::notifyListeners(TArray<FServerData> ServerData)
{
	for (UMainMenu* listener : Listeners)
	{
		listener->UpdateServerList(ServerData);
	}
}*/

void UDuckDuckInstance::JoinOnline(uint32 Index)
{
	if (SessionInterface.IsValid() && SessionSearch.IsValid())
	{
		SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
	}
}

void UDuckDuckInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		FString ConnectionString;
		if (SessionInterface->GetResolvedConnectString(SessionName, ConnectionString))
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (Controller)
			{
				Controller->ClientTravel(ConnectionString, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't join this session"));
	}
}