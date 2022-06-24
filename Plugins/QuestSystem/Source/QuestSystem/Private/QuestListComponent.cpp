// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestListComponent.h"

#include "Quest.h"
#include "CurrentObjectives.h"
#include "Blueprint/UserWidget.h"


// Sets default values for this component's properties
UQuestListComponent::UQuestListComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UQuestListComponent::BeginPlay()
{
	Super::BeginPlay();

	
	if (CurrentObjectivesWidget)
	{
		UCurrentObjectives* ObjectivesWidget = CreateWidget<UCurrentObjectives>(GetWorld(), CurrentObjectivesWidget);
		OnActiveQuestChanged.AddUObject(ObjectivesWidget, &UCurrentObjectives::SetCurrentObjectives);
		ObjectivesWidget->AddToViewport();
	}
	
}


// Called every frame
void UQuestListComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestListComponent::AddQuest(AQuest* Quest)
{
	if (Quest == nullptr)
		return;
	
	if (ActiveQuest == nullptr || ActiveQuest->IsCompleted())
	{
		ActiveQuest = Quest;
		OnActiveQuestChanged.Broadcast(ActiveQuest);
		
	}
	
	AcceptedQuests.Add(Quest);
	Quest->TakeQuest(GetOwner());

	Quest->OnQuestStatusChanged.AddLambda([this](AQuest* ChangedQuest)
	{
		if (ActiveQuest == ChangedQuest)
		{
			OnActiveQuestChanged.Broadcast(ChangedQuest);
		}
		
	});
	
}

void UQuestListComponent::SetActiveQuest(AQuest* Quest)
{
	if (AcceptedQuests.Contains(Quest))
	{
		ActiveQuest = Quest;
		OnActiveQuestChanged.Broadcast(ActiveQuest);
	}
}

