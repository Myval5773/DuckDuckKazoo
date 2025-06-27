// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerDisplayRow.h"

#include "Components/Button.h"

#include "MainMenu.h"

/*void UServerDisplayRow::Setup(UMainMenu* InMainMenuParent, uint32 InIndex)
{
	MainMenuParent = InMainMenuParent;
	Index = InIndex;
	if (RowButton)
	{
		RowButton->OnClicked.AddDynamic(this, &UServerDisplayRow::OnClicked);
	}
}*/

/*void UServerDisplayRow::OnClicked()
{
	if (MainMenuParent)
	{
		MainMenuParent->NotifyIndexSelected(Index);
	}
}*/

/*void UServerDisplayRow::SetDisplayData(const FServerData& InServerData)
{
	if (ServerName)
	{
		ServerName->SetText(FText::FromString(InServerData.Name));
	}
	if (HostName)
	{
		HostName->SetText(FText::FromString(InServerData.HostName));
	}
	if (AvailableAndMaxSlotsText)
	{
		FString PlayerCountString = FString::Printf(TEXT("%d/%d"), InServerData.CurrentPlayers, InServerData.MaxPlayers);
		AvailableAndMaxSlotsText->SetText(FText::FromString(PlayerCountString));
	}
}*/