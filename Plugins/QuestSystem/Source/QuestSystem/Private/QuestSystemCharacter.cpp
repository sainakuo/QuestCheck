// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemCharacter.h"

#include "QuestListComponent.h"
#include "Quest.h"
#include "QuestDialog.h"
#include "QuestList.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/WidgetComponent.h"
#include "NotificationWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AQuestSystemCharacter::AQuestSystemCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	NotificationWidget = CreateDefaultSubobject<UWidgetComponent>("NotificationWidget");
	NotificationWidget->SetWidgetClass(NotificationWidgetClass);
	NotificationWidget->SetupAttachment(RootComponent);
	NotificationWidget->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AQuestSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetAcceptableQuest();
	
}

// Called every frame
void AQuestSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuestSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AQuestSystemCharacter::Interact_Implementation(AActor* InteractInstigator)
{
	if (InteractInstigator == nullptr)
		return;

	UQuestListComponent* QuestList = Cast<UQuestListComponent>(InteractInstigator->GetComponentByClass(UQuestListComponent::StaticClass()));
	if (QuestList == nullptr)
	{
		return;
	}

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	
	for (auto& Actor: AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		
		Quest->OnQuestStatusChangedNoParams.AddUObject(this, &ThisClass::GetAcceptableQuest);

		if (Quest == nullptr)
			continue;

		if (Quest->bIsTaken || (Quest->PreviousQuest && !Quest->PreviousQuest->IsCompleted()))
		{
			continue;
		}
		
		if (QuestDialogClass)
		{
			UQuestDialog* QuestDialog = CreateWidget<UQuestDialog>(GetWorld(), QuestDialogClass);
			QuestDialog->Init(Quest);

			QuestDialog->OnQuestAccepted.AddUObject(QuestList, &UQuestListComponent::AddQuest, Quest);

			QuestDialog->OnQuestAccepted.AddUObject(this, &ThisClass::SetHiddenNotificationWidget, true);
			
			QuestDialog->onDialogExit.BindLambda([this, InteractInstigator]()
			{
				NotifyInteractionFinished(this, InteractInstigator);
			});
			
			QuestDialog->AddToViewport();
			
			return;
		}
	}
	
	NotifyInteractionFinished(this, InteractInstigator);
}

void AQuestSystemCharacter::GetAcceptableQuest()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	bool bAcceptableQuest = false;
	
	for (auto& Actor: AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);

		if (Quest == nullptr)
			continue;

		if (Quest->bIsTaken || (Quest->PreviousQuest && !Quest->PreviousQuest->IsCompleted()))
		{
			continue;
		}

		bAcceptableQuest = true;
	}

	SetHiddenNotificationWidget(!bAcceptableQuest);
}

void AQuestSystemCharacter::SetHiddenNotificationWidget(bool bSetHidden)
{
	if (NotificationWidget)
	{
		NotificationWidget->SetHiddenInGame(bSetHidden);
	}
}



