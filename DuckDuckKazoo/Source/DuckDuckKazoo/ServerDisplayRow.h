// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerDisplayRow.generated.h"

/**
 * 
 */
UCLASS()
class DUCKDUCKKAZOO_API UServerDisplayRow : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;

	UPROPERTY(meta = (BindWidget))
	class UMainMenu* MainMenuParent;

	uint32 Index;

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AvailableAndMaxSlotsText;

	//void Setup(class UMainMenu* InMainMenuParent, uint32 InIndex);

	//UFUNCTION()
	//void OnClicked();

	//void SetDisplayData(const FServerData& ServerData);
};
