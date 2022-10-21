// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	};
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	if (HasHit)
	{
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		//AActor* HitActor = HitResult.GetActor();
		//UE_LOG(LogTemp, Display, TEXT("hit: %s"),*HitActor->GetActorNameOrLabel()  );

	
		//Grabbing stuff
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	


	}	
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
		if( PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
		{	
			AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();	
			GrabbedActor->Tags.Remove("Grabbed");	
			PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
			PhysicsHandle->ReleaseComponent();
		}

}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
	{
		UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
		if(Result == nullptr) UE_LOG(LogTemp, Warning, TEXT("Grabber requires a UPhysicsHandleComponent."));
		return Result;

	}


bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;
	//DrawDebugLine( GetWorld(), start, end, FColor::Red );
	//DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5);


	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel( 
		OutHitResult, 
		start, 
		end, 
		FQuat::Identity, 
		ECC_GameTraceChannel2, 
		Sphere);

}
