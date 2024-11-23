// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/XPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "XGameplayTags.h"
#include "AbilitySystems/XAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/XEnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

AXPlayerController::AXPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AXPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
	
}

void AXPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(XPlayerContext); //检测XPlayerContext是否有效
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem) //只有LocalPlayer的Client才会获得Subsystem
	{
		Subsystem->AddMappingContext(XPlayerContext, 0);
	}
	

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UXEnhancedInputComponent* EnhancedInputComponent = CastChecked<UXEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXPlayerController::Move);
	EnhancedInputComponent->BindInputActionFunction(InputConfig,this,&AXPlayerController::PressedFunc,&AXPlayerController::ReleasedFunc,&AXPlayerController::HeldFunc);
}

void AXPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
}

void AXPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, VisibilityCursorHit);
	if (!VisibilityCursorHit.bBlockingHit) return;
	LastActor = CurActor;
	CurActor = VisibilityCursorHit.GetActor();

	if(LastActor != CurActor)
	{
		if(LastActor) LastActor->UnHighlightActor();
		if(CurActor) CurActor->HighlightActor();
	}
}

void AXPlayerController::PressedFunc(FGameplayTag GameplayTag)
{
	//GEngine->AddOnScreenDebugMessage(1,2.0f,FColor::Blue,*GameplayTag.ToString());
	if(GameplayTag.MatchesTagExact(XGameplayTags::GetInstance().InputTag_LMB)) // just for left mouse button we need choose
	{
		bTarget = CurActor ? true : false;
		bAutoRunning = false;
	}
}

void AXPlayerController::ReleasedFunc(FGameplayTag GameplayTag)
{
	//GEngine->AddOnScreenDebugMessage(2,2.0f,FColor::Red,*GameplayTag.ToString());
	if(!GameplayTag.MatchesTagExact(XGameplayTags::GetInstance().InputTag_LMB))
	{
		if(GetXASC()) GetXASC()->AbilityInputTagRealesed(GameplayTag);
		return ;
	}
	if(bTarget)
	{
		if(GetXASC()) GetXASC()->AbilityInputTagRealesed(GameplayTag);
	}
	else
	{
		APawn* CurPawn = GetPawn();
		if(FollowTime <= ShortPressThreshold && CurPawn)
		{
			UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, CurPawn->GetActorLocation(), CachedDestination);
			if(NavPath)
			{
				// NavPath->PathPoints: Array of FVector from actorlocation to goallocation
				//we need use this points create the spline
				Spline->ClearSplinePoints();
				for(const FVector& PointVec : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointVec,ESplineCoordinateSpace::World);
				}
				CachedDestination = NavPath->PathPoints.Last();
				bAutoRunning = true;
			}
		}
		FollowTime = 0.0f;
		bTarget = false;
	}
	
}

void AXPlayerController::HeldFunc(FGameplayTag GameplayTag)
{
	//GEngine->AddOnScreenDebugMessage(2,2.0f,FColor::Green,*GameplayTag.ToString());
	if(!GameplayTag.MatchesTagExact(XGameplayTags::GetInstance().InputTag_LMB))
	{
		if(GetXASC()) GetXASC()->AbilityInputTagHeld(GameplayTag);
		return ;
	}
	//think about running
	if(bTarget)
	{
		if(GetXASC()) GetXASC()->AbilityInputTagHeld(GameplayTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if(VisibilityCursorHit.IsValidBlockingHit())
		{
			CachedDestination = VisibilityCursorHit.ImpactPoint;
		}
		if(APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UXAbilitySystemComponent* AXPlayerController::GetXASC()
{
	if(XAbilitySystemComponent == nullptr)
	{
		XAbilitySystemComponent = Cast<UXAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return XAbilitySystemComponent;
}

void AXPlayerController::AutoRun()
{
	if(!bAutoRunning) return;
	if(APawn* ControlledPawn = GetPawn())
	{
		//the location in spline which near the player location
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);

		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if(DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
