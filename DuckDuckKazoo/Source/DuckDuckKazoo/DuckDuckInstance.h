// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "DuckDuckInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUCKDUCKKAZOO_API UDuckDuckInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDuckDuckInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& IPAddress);

	UFUNCTION(Exec, BlueprintCallable)
	void OpenMenu();

	UFUNCTION(Exec)
	void SearchAvailableSessions();

	UFUNCTION(Exec)
	void CreateASession();

	UFUNCTION(Exec)
	void StartSingleplayerMode(FName MapName);

	UFUNCTION(Exec)
	void QuitGame();

protected:
	virtual void Init();

	UPROPERTY()
	TSubclassOf<class UUserWidget> OnlineMenu;

	UPROPERTY()
	TSubclassOf<class UUserWidget> MainMenu;

	UPROPERTY()
	TSubclassOf<class UUserWidget> JoinMenu;

private:
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate OnFindSessionCompleteDelegate;
	FDelegateHandle OnFindSessionCompleteDelegateHandle;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	//void OnFindSessionsComplete(bool bWasSuccessful);	
};
