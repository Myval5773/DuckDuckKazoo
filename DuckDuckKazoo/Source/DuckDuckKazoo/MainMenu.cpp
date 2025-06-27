// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "DuckDuckInstance.h"

#include "Components/WidgetSwitcher.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/EditableText.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensure(SingleplayerButton != nullptr)) return;

	if (!ensure(LocalButton != nullptr)) return;
	if (!ensure(LocalJoinButton != nullptr)) return;
	if (!ensure(LocalHostButton != nullptr)) return;
	if (!ensure(LocalCancelButton != nullptr)) return;
	if (!ensure(LocalConfirmButton != nullptr)) return;
	if (!ensure(IPAddressField != nullptr)) return;

	if (!ensure(OnlineButton != nullptr)) return;
	if (!ensure(OnlineHostButton != nullptr)) return;
	if (!ensure(OnlineJoinButton != nullptr)) return;
	if (!ensure(OnlineCancelButton != nullptr)) return;
	if (!ensure(OnlineConfirmButton != nullptr)) return;

	if (!ensure(QuitButton != nullptr)) return;

	if (!ensure(MenuSwitcher != nullptr)) return;

	// Singleplayer
	SingleplayerButton->OnClicked.AddDynamic(this, &UMainMenu::OnSingleplayerButtonClicked);

	// Local
	LocalButton->OnClicked.AddDynamic(this, &UMainMenu::OnLocalButtonClicked);
	LocalHostButton->OnClicked.AddDynamic(this, &UMainMenu::OnLocalHostButtonClicked);
	LocalJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OnLocalJoinButtonClicked);
	LocalCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OnLocalCancelButtonClicked);
	LocalConfirmButton->OnClicked.AddDynamic(this, &UMainMenu::OnLocalConfirmButtonClicked);

	// Online
	OnlineButton->OnClicked.AddDynamic(this, &UMainMenu::OnOnlineButtonClicked);
	OnlineHostButton->OnClicked.AddDynamic(this, &UMainMenu::OnOnlineHostButtonClicked);
	OnlineJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OnOnlineJoinButtonClicked);
	OnlineCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OnOnlineCancelButtonClicked);
	OnlineConfirmButton->OnClicked.AddDynamic(this, &UMainMenu::OnOnlineConfirmButtonClicked);

	// Quit
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitButtonClicked);

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) { return; };	

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = true;
}

void UMainMenu::NativeDestruct() {
	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(true);
	if (GetWorld() != nullptr && GetWorld()->GetFirstPlayerController() != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeData);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	}

	Super::NativeDestruct();
}


void UMainMenu::SetGameInstance(UDuckDuckInstance* GameInstance) {
	if (!ensure(GameInstance != nullptr)) return;
	DuckDuckInstance = GameInstance;
}

void UMainMenu::OnSingleplayerButtonClicked() 
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	if (!ensure(Controller != nullptr)) return;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; };
	World->AddController(Controller);
	if (DuckDuckInstance != nullptr)
	{
		DuckDuckInstance->StartSingleplayerMode(MapName);
	}
}

void UMainMenu::OnQuitButtonClicked()
{
	if (DuckDuckInstance != nullptr)
	{
		DuckDuckInstance->QuitGame();
	}
}

void UMainMenu::OnLocalButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(1);
	}
}

void UMainMenu::OnLocalHostButtonClicked()
{
	if (DuckDuckInstance)
	{
		DuckDuckInstance->HostLocally();
	}
}

void UMainMenu::OnLocalJoinButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(3);
	}
}

void UMainMenu::OnLocalCancelButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(0);
	}
}

void UMainMenu::OnLocalConfirmButtonClicked()
{
	FText IPAddressToJoin = IPAddressField->GetText();
	FString IPAddressToJoinString = IPAddressToJoin.ToString();
	if (DuckDuckInstance)
	{
		DuckDuckInstance->JoinLocally(*IPAddressToJoinString);
	}
}

void UMainMenu::OnOnlineButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(2);
	}
}

void UMainMenu::OnOnlineHostButtonClicked()
{
	if (DuckDuckInstance)
	{
		UE_LOG(LogTemp,Warning, TEXT("Host Online button clicked"))
		DuckDuckInstance->HostOnline();
	}
}

void UMainMenu::OnOnlineJoinButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(4);
	}
}

void UMainMenu::OnOnlineCancelButtonClicked()
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidgetIndex(0);
	}
}

void UMainMenu::OnOnlineConfirmButtonClicked()
{
	if (DuckDuckInstance)
	{
		//DuckDuckInstance->JoinSession();
	}
}
