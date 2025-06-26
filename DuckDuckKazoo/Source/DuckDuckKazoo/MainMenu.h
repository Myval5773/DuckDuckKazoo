// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class DUCKDUCKKAZOO_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Singleplayer properties
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> SingleplayerButton;

	// Local multiplayer properties
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LocalButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LocalHostButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LocalJoinButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LocalCancelButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LocalConfirmButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* IPAddressField;

	// Online multiplayer properties
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnlineButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnlineHostButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnlineJoinButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnlineCancelButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnlineConfirmButton;


	// Quit properties
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;


	// Widget properties
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

public:
	void SetGameInstance(class UDuckDuckInstance* GameInstance);
	FName MapName = "MainMap";

private:
	class UDuckDuckInstance* DuckDuckInstance;

	UFUNCTION(Exec)
	void OnSingleplayerButtonClicked();

	UFUNCTION(Exec)
	void OnQuitButtonClicked();

	UFUNCTION(Exec)
	void OnLocalButtonClicked();

	UFUNCTION(Exec)
	void OnLocalHostButtonClicked();

	UFUNCTION(Exec)
	void OnLocalJoinButtonClicked();

	UFUNCTION(Exec)
	void OnLocalCancelButtonClicked();

	UFUNCTION(Exec)
	void OnLocalConfirmButtonClicked();
	
	UFUNCTION(Exec)
	void OnOnlineButtonClicked();

	UFUNCTION(Exec)
	void OnOnlineHostButtonClicked();

	UFUNCTION(Exec)
	void OnOnlineJoinButtonClicked();

	UFUNCTION(Exec)
	void OnOnlineCancelButtonClicked();

	UFUNCTION(Exec)
	void OnOnlineConfirmButtonClicked();
};
