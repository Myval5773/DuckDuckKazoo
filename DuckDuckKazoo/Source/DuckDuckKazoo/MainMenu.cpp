// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "DuckDuckInstance.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensure(SingleplayerButton != nullptr)) return;
	if (!ensure(LocalButton != nullptr)) return;
	if (!ensure(OnlineButton != nullptr)) return;
	if (!ensure(QuitButton != nullptr)) return;

	SingleplayerButton->OnClicked.AddDynamic(this, &UMainMenu::SingleplayerButtonClicked);
	//LocalButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinButtonClicked);
	//OnlineButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoinMenu);
	//QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonClicked);

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

void UMainMenu::SingleplayerButtonClicked() 
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

void UMainMenu::QuitButtonClicked()
{
	if (DuckDuckInstance != nullptr)
	{
		DuckDuckInstance->QuitGame();
	}
}
