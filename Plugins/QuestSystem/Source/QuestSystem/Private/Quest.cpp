// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

#include "Objective.h"


// Sets default values
AQuest::AQuest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();

	AActor* ParentActor = GetAttachParentActor();
/*
	if (ParentActor)
	{
		TakeQuest(ParentActor);
	}
	*/
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuest::UpdateLocation()
{
	AActor* ParentActor = GetAttachParentActor();

	if (ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

void AQuest::TakeQuest(AActor* Character)
{
	if (bIsTaken)
	{
		return;
	}

	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		auto* Objective = Objectives[i];
		if (Objective == nullptr)
		{
			continue;
		}

		Objective->ActivateObjective(Character);
		Objective->bCanBeCompleted = i == 0 || !bKeepObjectivesOrder;
		Objective->OnObjectiveCompleted.AddUObject(this, &ThisClass::OnObjectiveCompleted);
	}
	
	bIsTaken = true;
}

void AQuest::OnObjectiveCompleted(UObjective* Objective)
{
	if (bKeepObjectivesOrder)
	{
		int32 Index;
		if (Objectives.Find(Objective, Index) && Objectives.IsValidIndex(Index + 1))
		{
			Objectives[Index+1]->bCanBeCompleted = true;
		}
	}

	for (int32 i = 0; i < Objectives.Num(); i++)
	{
		auto* Objective = Objectives[i];

		if (!Objective->bIsCompleted)
		{
			QuestStatus = false;
			return;
		}
	}

	QuestStatus = true;
	OnQuestStatusChanged.Broadcast(this);
	OnQuestStatusChangedNoParams.Broadcast();
}

bool AQuest::IsCompleted()
{
	return QuestStatus;
}

bool AQuest::IsStoryQuest()
{
	return bIsStoryQuest;
}

FText& AQuest::GetName()
{
	return Name;
}

#if WITH_EDITOR

TArray<UObjective*>& AQuest::GetObjectives()
{
	return Objectives;
}

void AQuest::AddInteractObjective()
{
	Objectives.Add(NewObject<UInteractionObjective>(this));
}

void AQuest::AddLocationtObjective()
{
	Objectives.Add(NewObject<ULocationObjective>(this));
}

#endif