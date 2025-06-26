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

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> SingleplayerButton;

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


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnlineButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

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
};
