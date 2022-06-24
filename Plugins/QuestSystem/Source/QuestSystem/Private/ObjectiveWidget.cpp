// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWidget.h"

#include "Objective.h"
#include "Components/TextBlock.h"

void UObjectiveWidget::Init(UObjective* Objective)
{
	if (Objective == nullptr)
	{
		return;
	}

	CompletedCheck->SetIsChecked(Objective->bIsCompleted);
	DescriptionText->SetText(Objective->Description);

	Objective->OnObjectiveCompleted.AddUObject(this, &ThisClass::UpdateCheckBox);
}


void UObjectiveWidget::UpdateCheckBox(UObjective* Objective)
{
	CompletedCheck->SetIsChecked(Objective->bIsCompleted);
}