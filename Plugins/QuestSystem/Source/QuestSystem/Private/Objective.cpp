// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"

#include "InteractableObject.h"
#include "LocationMarker.h"

UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Ot_Interact;
}

void UInteractionObjective::ActivateObjective(AActor* Instigator)
{
	
	if (auto* InteractTarget = Cast<IInteractableObject>(Target))
	{
		InteractTarget->OnInteractionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
			if (bCanBeCompleted && Instigator == InteractInstigator)
			{
				bIsCompleted = true;
				OnObjectiveCompleted.Broadcast(this);
			}
		});
	}
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Ot_Location;
}

void ULocationObjective::ActivateObjective(AActor* Instigator)
{
	if (auto* InteractTarget = Cast<ILocationMarker>(Marker))
	{
		InteractTarget->OnLocationReached.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
			if (bCanBeCompleted && Instigator == InteractInstigator)
			{
				bIsCompleted = true;
				OnObjectiveCompleted.Broadcast(this);
			}
		});
	}
}
