// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestDialog.h"

#include "QuestDescription.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UQuestDialog::NativeConstruct()
{
	Super::NativeConstruct();

	if (AcceptButton)
     	{
     		AcceptButton->OnReleased.AddDynamic(this, &ThisClass::OnAccepted);
     	}

	if (RejectButton)
	{
		RejectButton->OnReleased.AddDynamic(this, &ThisClass::OnRejected);
	}

	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC, this);
	PC->SetShowMouseCursor(true);
}

void UQuestDialog::Init(AQuest* Quest)
{
	if (Description)
		Description->Init(Quest);
}

void UQuestDialog::OnAccepted()
{
	HideDialog();
	OnQuestAccepted.Broadcast();

}

void UQuestDialog::OnRejected()
{
	HideDialog();
}

void UQuestDialog::HideDialog()
{
	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	PC->SetShowMouseCursor(false);

	RemoveFromViewport();

	onDialogExit.ExecuteIfBound();
}
