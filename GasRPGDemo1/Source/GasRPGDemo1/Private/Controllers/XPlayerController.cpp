// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/XPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AXPlayerController::AXPlayerController()
{
	bReplicates = true;
}

void AXPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AXPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(XPlayerContext); //ºÏ≤‚XPlayerContext «∑Ò”––ß
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(XPlayerContext, 0);

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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXPlayerController::Move);
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
	
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	LastActor = CurActor;
	CurActor = CursorHit.GetActor();
	/*
	* a. lastactor is null && curactor is null
	*  - do nothing
	* b. lastactor is null && curactor isn't null
	*  - do highlight
	* c. lastactor isn't null && curactor isn't null && lastactor != curactor
	*  - lastactor do unhighlight curactor do hightlight
	* d. lastactor isn't null && curactor is null
	*  - lastactor do unhighlight
	* e. lastactor isn't null && curactor isn't null && lastactor == curactor
	*  - do nothing
	*/
	if (!LastActor)
	{
		if (CurActor)
		{
			// b
			CurActor->HighlightActor();
		}
		// a
	}
	else
	{
		if (!CurActor)
		{
			// d
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != CurActor)
			{
				// c
				LastActor->UnHighlightActor();
				CurActor->HighlightActor();
			}
		}
		// e
	}
}
