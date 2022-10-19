// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //sprawdzanie czy przedmiot ma odpoiwedni tag żeby otworzyć drzwi
    AActor* Actor = GetAcceptableActorTag();
    if (IsValid(Actor))
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>( Actor->GetRootComponent() );
        if(IsValid(Component))
            {
                Component->SetSimulatePhysics(false);
            }
        Actor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform); 
        Mover->setShouldMove(true);
    }
    else
    {
        Mover->setShouldMove(false);
    }    
}

//#CrashPosibility
void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}


AActor* UTriggerComponent::GetAcceptableActorTag() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);      
    for(AActor* Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if ( HasAcceptableTag && !IsGrabbed )
        {
            return Actor;
        }
    }

    return nullptr;
}