// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
//#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UTriggerComponent();	//constructor

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
/*
	//#CrashPosibility
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);


private: 

	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;

	//#CrashPosibility
	UMover* Mover;

	AActor* GetAcceptableActorTag() const;
*/
};
