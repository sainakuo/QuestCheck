// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestDescription.h"
#include "QuestListComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "QuestList.generated.h"

class UQuestListEntry;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestList : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UQuestListComponent* QuestList);

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox *StoryQuestList;

	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox *SideQuestList;

	UPROPERTY(meta = (BindWidgetOptional))
	UQuestDescription* ActiveQuestDescription;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestListEntry> QuestEntryClass;
	
	UPROPERTY()
	TMap<AQuest*, UQuestListEntry*> QuestEntries;
	
	void OnActiveQuestChanged(AQuest * ActiveQuest);
};
