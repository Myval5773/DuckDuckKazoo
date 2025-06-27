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
#include "Engine/World.h"

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

	UFUNCTION(Exec, BlueprintCallable)
	void OpenMenu();

	UFUNCTION(Exec)
	void HostLocally();

	UFUNCTION(Exec)
	void LaunchGame();

	UFUNCTION(Exec)
	void JoinLocally(const FString& IPAddress);

	UFUNCTION(Exec)
	void StartSingleplayerMode(FName MapName);

	UFUNCTION(Exec)
	void QuitGame();

	// Online Subsystem host methods
	UFUNCTION(Exec)
	void HostOnline();

	UFUNCTION(Exec)
	void CreateASession();

	// Online Subsystem join methods
	UFUNCTION(Exec)
	void SearchAvailableSessions();
	

protected:
	virtual void Init();

	UPROPERTY()
	TSubclassOf<class UUserWidget> OnlineMenu;

	UPROPERTY()
	TSubclassOf<class UUserWidget> MainMenu;

	UPROPERTY()
	TSubclassOf<class UUserWidget> JoinMenu;

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate OnFindSessionCompleteDelegate;
	FDelegateHandle OnFindSessionCompleteDelegateHandle;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
};
