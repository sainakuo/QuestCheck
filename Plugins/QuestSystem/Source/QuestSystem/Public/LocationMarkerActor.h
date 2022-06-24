﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LocationMarker.h"
#include "GameFramework/Actor.h"
#include "LocationMarkerActor.generated.h"


UCLASS()
class QUESTSYSTEM_API ALocationMarkerActor : public AActor, public ILocationMarker
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnOverlappedByActor(AActor* OverlappingActor)
	{
		NotifyOverlapWithActor(this, OverlappingActor);
	}
	
};
