// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "GameFramework/Character.h"
#include "QuestSystemCharacter.generated.h"

class UQuestList;
class UQuestDialog;
class UNotificationWidget;
class AQuest;

UCLASS()
class QUESTSYSTEM_API AQuestSystemCharacter : public ACharacter, public IInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuestSystemCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact_Implementation(AActor* InteractInstigator) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuestDialog> QuestDialogClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TSubclassOf<UNotificationWidget> NotificationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UWidgetComponent* NotificationWidget;

	UFUNCTION()
	void GetAcceptableQuest();

	UFUNCTION()
	void SetHiddenNotificationWidget(bool bSetHidden);
};
