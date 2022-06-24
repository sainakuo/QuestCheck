// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrentObjectives.h"
#include "Quest.h"
#include "ObjectiveWidget.h"

void UCurrentObjectives::SetCurrentObjectives(AQuest* Quest)
{
	if (ObjectivesList && ObjectiveWidgetClass)
	{
		ObjectivesList->ClearChildren();
		for (auto* Objective: Quest->GetObjectives())
		{
			auto* ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
			ObjectiveWidget->Init(Objective);
			ObjectivesList->AddChildToVerticalBox(ObjectiveWidget);
		}
	}
}
