// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Floor.h"
#include "Hatchet.h"
#include "AssaultRifle.h"
#include "Crossbow.h"
#include "Components/CapsuleComponent.h"
#include "InteractionComponent.h"
#include "Net/UnrealNetwork.h"




//
// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;
	// ...

	InventoryTest = CreateDefaultSubobject<UInventoryTest>(TEXT("InventoryTest"));

	Handle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Handle"));
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh(), FName("head"));

	InteractionCheckFrequency = 0;
	InteractionCheckDistance = 1000;	

	ArrayValues();
}
void AMyCharacter::ArrayValues()
{
	//To calculate location it's just using absolute location and then subtracting the values
	// For Relative it's just where it's located without subtraction relitviily





	//Check outhit and figure out if then subtract the x and y

	FloorSnapLocation.Add(FVector(-280, 0, 0));
	FloorSnapLocation.Add(FVector(280, 0, 0));
	FloorSnapLocation.Add(FVector(0, 280, 0));
	FloorSnapLocation.Add(FVector(0, -280, 0));
	FloorSnapLocation.Add(FVector(242, -139.162, 0));
	FloorSnapLocation.Add(FVector(-242, 139.162, 0));
	FloorSnapLocation.Add(FVector(-139.162, -242,  0));
	FloorSnapLocation.Add(FVector(139.162, 242,  0));
	FloorSnapLocation.Add(FVector(139.201f, -242, 0 ));
	FloorSnapLocation.Add(FVector(-139.201f, 242, 0 ));
	FloorSnapLocation.Add(FVector(-242, -139.201f, 0 ));
	FloorSnapLocation.Add(FVector(242, 139.201f, 0 ));

	FloorTriangleSnapLocation.Add(FVector(-221, 0,0));
	FloorTriangleSnapLocation.Add(FVector(221, 0,0));
	FloorTriangleSnapLocation.Add(FVector(0, 221,0));
	FloorTriangleSnapLocation.Add(FVector(0, -221,0));
	FloorTriangleSnapLocation.Add(FVector(-110, -191.5,0));
	FloorTriangleSnapLocation.Add(FVector(110, 191.5,0));
	FloorTriangleSnapLocation.Add(FVector(-191.5, 110,0));
	FloorTriangleSnapLocation.Add(FVector(191.5, -110,0));

	FloorToTriangleSnapLocation.Add(FVector(-191, 111, 0));
	FloorToTriangleSnapLocation.Add(FVector(191, 111, 0));
	FloorToTriangleSnapLocation.Add(FVector(0, -220, 0));
	FloorToTriangleSnapLocation.Add(FVector(-191, -111, 0));
	FloorToTriangleSnapLocation.Add(FVector(191, -111, 0));
	FloorToTriangleSnapLocation.Add(FVector(0, 220, 0));
	FloorToTriangleSnapLocation.Add(FVector(111, -191, 0));
	FloorToTriangleSnapLocation.Add(FVector(111, 191 , 0));
	FloorToTriangleSnapLocation.Add(FVector(-220, 0, 0));
	FloorToTriangleSnapLocation.Add(FVector(-111, -191 , 0));
	FloorToTriangleSnapLocation.Add(FVector(-111, 191 , 0));
	FloorToTriangleSnapLocation.Add(FVector(220, 0, 0));
	FloorToTriangleSnapLocation.Add(FVector(111, 191, 0));
	FloorToTriangleSnapLocation.Add(FVector(111, -191, 0));
	FloorToTriangleSnapLocation.Add(FVector(-220, 0, 0));

//FIRST ONE

	TriangleSnapLocation.Add(FVector(-140.25f, 80, 0));
	TriangleSnapLocation.Add(FVector(140.25f, 80, 0));
	TriangleSnapLocation.Add(FVector(0, -160, 0));
	TriangleSnapLocation.Add(FVector(-140.25f, -80, 0));
	TriangleSnapLocation.Add(FVector(140.25f, -80, 0));
	TriangleSnapLocation.Add(FVector(0, 160, 0));
	TriangleSnapLocation.Add(FVector(80, -140.25f , 0));
	TriangleSnapLocation.Add(FVector(80, 140.25f , 0));
	TriangleSnapLocation.Add(FVector(-160, 0, 0));
	TriangleSnapLocation.Add(FVector(-80, -140.25f , 0));
	TriangleSnapLocation.Add(FVector(-80, 140.25f , 0));
	TriangleSnapLocation.Add(FVector(160, 0, 0));
	TriangleSnapLocation.Add(FVector(80, 140.25f, 0));
	TriangleSnapLocation.Add(FVector(80, -140.25f, 0));
	TriangleSnapLocation.Add(FVector(-160, 0, 0));

	TriangleWallSnapLocation.Add(FVector(0, 0, -7.3));
	TriangleWallSnapLocation.Add(FVector(-0.41, 0.534, -7.3));
	TriangleWallSnapLocation.Add(FVector(-0.190, 1.112, -7.3));
	TriangleWallSnapLocation.Add(FVector(-0.03, -0.1, -7.3));
	TriangleWallSnapLocation.Add(FVector(0.611, -0.139, -7.3));
	TriangleWallSnapLocation.Add(FVector(0.3, 0.07, -7.3));
	TriangleWallSnapLocation.Add(FVector(-0.84, 0.225, -7.3));
	TriangleWallSnapLocation.Add(FVector(-0.3, 0.534, -7.3));
	TriangleWallSnapLocation.Add(FVector(0, 0, -7.3));
	TriangleWallSnapLocation.Add(FVector(0.2, 0.5, -7.3));

	WallSnapLocation.Add(FVector(-130, 0, 0));
	WallSnapLocation.Add(FVector(130, 0, 0));
	WallSnapLocation.Add(FVector(0, 130, 0));
	WallSnapLocation.Add(FVector(0, -130, 0));

	RoofSnapLocation.Add(FVector(-280, 0 , 0));
	RoofSnapLocation.Add(FVector(280, 0 , 0));
	RoofSnapLocation.Add(FVector(0, 280, 0));
	RoofSnapLocation.Add(FVector(0, -280 , 0));

	//Lengths of the different things like walls, floors etc
	BuildingTypes.Add(FVector(1.4, 1.4, 1.f));
	BuildingTypes.Add(FVector(0.2f, 2.8f, 3.f));
	BuildingTypes.Add(FVector(2.8f, 2.8f, 0.3f));
	BuildingTypes.Add(FVector(1.62f, 1.62f, 0.75f));
	BuildingTypes.Add(FVector(1,1,1));
}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(Camera->HasAnySockets() && Camera != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("has sockets"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No socket"))
	}
	Ammo = 25;
	InteractPure();

	PlayerCapsule = this->GetCapsuleComponent();
	PlayerCapsule->GetScaledCapsuleSize(OutRadius, OutHalfHeight);
	
	
	if(Waves != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Waves, FVector(0,0,0));
	}

	if(FloorClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Floorclass is nullptr"))
	}
	//need a better check here for ai
	if (IsPlayerControlled() == false)
	{
		AR = GetWorld()->SpawnActor<AAssaultRifle>(GunClass);
		AR->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
		AR->SetOwner(this);
	}

	TraceParams.AddIgnoredActor(this);
	

	FindPlayer();
}

void AMyCharacter::Tick(float DeltaTime)
{
	//Don't use GetOwner before actor location in tick
	Super::Tick(DeltaTime);
	
	if(GetController() != nullptr)
	{
		if(AllowBuilding || Handle->GetGrabbedComponent() != nullptr || IsCrossBow)
		{
			GetController()->GetPlayerViewPoint(PlacementLocation, PlacementRotation);
			LineTraceEnd = (PlacementLocation + PlacementRotation.Vector() * 600);
			LengthOfGrabber = (PlacementLocation + PlacementRotation.Vector() * GrabLength);
			GetWorld()->LineTraceSingleByChannel(OutHit, PlacementLocation, LineTraceEnd, ECC_Visibility, TraceParams);
		}
	}


	if (Handle->GetGrabbedComponent() != nullptr)
	{
		//testing
		if (FVector::Distance(GetActorLocation(), Handle->GetGrabbedComponent()->GetComponentLocation()) < 100 || PlayerIsJumping == true)
		{
			ReleaseDrop();
		}
		Handle->SetTargetLocationAndRotation(LengthOfGrabber, PlacementRotation);
		
	}

	if(IsFireHeld == true && GetWorldTimerManager().IsTimerActive(HatchetSwingDelay) == false)
	{
		LeftClick();
		// Works just needs to be optimized that way it only runs this if it's not already be ran
	}
	//interactionsystem
	
	const bool IsInteractingOnServer = (HasAuthority() && IsInteracting());

	if(!HasAuthority() || IsInteractingOnServer && GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
	
}

//INPUT
//Movement, firing, reloading
// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("XLookDirection"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("YLookDirection"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis(TEXT("XMovement"), this, &AMyCharacter::XMovement);
	PlayerInputComponent->BindAxis(TEXT("YMovement"), this, &AMyCharacter::YMovement);

	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AMyCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AMyCharacter::SprintRelease);
	PlayerInputComponent->BindAction(TEXT("Extend"), EInputEvent::IE_Repeat, this, &AMyCharacter::GrabExtend);
	PlayerInputComponent->BindAction(TEXT("Detract"), EInputEvent::IE_Repeat, this, &AMyCharacter::GrabDetract);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::StartJump);
	//do not switch these two crouches doing so will result in the toggle breaking CrouchEnd always first here, Crouch second. The reason for this is you need the crouchend to run before crouch so Crouchend doesn't try to run first and break the process
	//PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AMyCharacter::CrouchEnd);
	//PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AMyCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("Grab"), EInputEvent::IE_Pressed, this, &AMyCharacter::Grab);
	PlayerInputComponent->BindAction(TEXT("Grab"), EInputEvent::IE_Released, this, &AMyCharacter::ReleaseThrow);

	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AMyCharacter::BeginInteract);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Released, this, &AMyCharacter::EndInteract);

	//PlayerInputComponent->BindAction(TEXT("BuildMenu"), EInputEvent::IE_Pressed, this, &AMyCharacter::BuildMenu);

	
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMyCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &AMyCharacter::FireReleased);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AMyCharacter::Reload);

//	PlayerInputComponent->BindAction(TEXT("Weapon1"), EInputEvent::IE_Pressed, this, &AMyCharacter::ServerWeapon1);
//	PlayerInputComponent->BindAction(TEXT("Weapon2"), EInputEvent::IE_Pressed, this, &AMyCharacter::ServerWeapon1);
}
void AMyCharacter::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, YInput);
	DOREPLIFETIME(AMyCharacter, XInput);
	DOREPLIFETIME(AMyCharacter, IsHatchet);
	DOREPLIFETIME(AMyCharacter, IsAR);
	DOREPLIFETIME(AMyCharacter, IsCrossBow);
	DOREPLIFETIME(AMyCharacter, AR);
	DOREPLIFETIME(AMyCharacter, CrossBow);
	DOREPLIFETIME(AMyCharacter, Hatchet)
	DOREPLIFETIME(AMyCharacter, WalkSpeed);
	DOREPLIFETIME(AMyCharacter, Health);
	DOREPLIFETIME(AMyCharacter, SwingAxe);
	DOREPLIFETIME(AMyCharacter, Wood);
}
void AMyCharacter::ServerYMovement_Implementation(float AxisValue)
{
	YMovement(AxisValue);
}
void AMyCharacter::ServerXMovement_Implementation(float AxisValue)
{
	XMovement(AxisValue);
}

void AMyCharacter::XMovement(float AxisValue)
{	
	if(!HasAuthority())
	{
		ServerXMovement(AxisValue);
	}
	if(XInput != 0 && YInput == 0 && WalkSpeed != 1)
	{
		WalkSpeed = 0.55;
	}
	AddMovementInput(GetActorRightVector()* AxisValue * WalkSpeed);
	XInput = AxisValue;

}
void AMyCharacter::YMovement(float AxisValue)
{	
	if(!HasAuthority())
	{
		ServerYMovement(AxisValue);
	}
	else if(XInput != 0 && YInput != 0 && WalkSpeed != 1)
	{
		WalkSpeed = 0.35;
		
	}
	else if(WalkSpeed != 1)
	{
		WalkSpeed = 0.60;
		
	}

	AddMovementInput(GetActorForwardVector()* AxisValue, WalkSpeed);
	YInput = AxisValue;
	
	
}


void AMyCharacter::Sprint()
{
	
	if(!HasAuthority())
	{
		ServerSprint();
	}
	if(!(XInput < 0 && YInput < 0) && !(XInput > 0 && YInput < 0))
	{
		WalkSpeed = 1;
		
	}
}
void AMyCharacter::ServerSprint_Implementation()
{
	Sprint();
}
void AMyCharacter::ServerSprintRelease_Implementation()
{
	SprintRelease();
}
void AMyCharacter::SprintRelease()
{
	if(!HasAuthority())
	{
		ServerSprintRelease();
	}
	WalkSpeed = 0.6;
}
//Weapon Switching
void AMyCharacter::ServerPlayerToolbar_Implementation(const FKey Key, const FString& ToolName)
{
	//if the key has been pressed twice then it resets

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s Key"), *Key.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s itemname"), *ToolName));
	//this is going to need to check tool name later.
	
	if (IsGrabbing != false || PlayerIsJumping != false){return;}

//basically instead of the if statements have a hardcoded variable it would be Toolname and then finding a way to spawn that efficently

	if(Key.ToString() == "One" && IsAR == false)
	{
		AR = GetWorld()->SpawnActor<AAssaultRifle>(GunClass);
		AR->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
		AR->SetOwner(this);
		IsAR = true;
		if(Hatchet != nullptr)
		{
			Hatchet->Destroy();
			IsHatchet = false;
		}
		else if(CrossBow != nullptr)
		{
			CrossBow->Destroy();
			IsCrossBow = false;
		}
	}
	else if(Key.ToString() == "Two" && IsHatchet == false)
	{
		Hatchet = GetWorld()->SpawnActor<AHatchet>(HatchetClass);
		Hatchet->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("HatchetSocket"));
		Hatchet->SetOwner(this);
		IsHatchet = true;
		if(AR != nullptr)
		{
			AR->Destroy();
			IsAR = false;
		}
		else if(CrossBow != nullptr)
		{
			CrossBow->Destroy();
			IsCrossBow = false;
		}
	}
	else if(Key.ToString() == "Three" && IsCrossBow == false)
	{
		CrossBow = GetWorld()->SpawnActor<ACrossbow>(CrossBowClass);
		CrossBow->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
		CrossBow->SetOwner(this);
		IsCrossBow = true;
		if(AR != nullptr)
		{
			AR->Destroy();
			IsAR = false;
		}
		else if(Hatchet != nullptr)
		{
			Hatchet->Destroy();
			Hatchet = false;
		}
	}
	else if (IsAR == true && PlayerIsJumping == false && AR != nullptr)
	{
		AR->Destroy();
		IsAR = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("AR Destroyed")));
	}
	else if (IsHatchet == true && PlayerIsJumping == false && Hatchet != nullptr)
	{
		Hatchet->Destroy();
		IsHatchet = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("HATCHET Destroyed")));
	}
	else if (IsCrossBow == true && PlayerIsJumping == false && CrossBow != nullptr)
	{
		CrossBow->Destroy();
		IsCrossBow = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("CrossBow Destroyed")));
	}

	if(IsAR == true || IsHatchet == true)
	{
		ReleaseDrop();
	}

	//so Crossbow does get to hear
	// if(CrossBow != nullptr)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("CrossBow still here")));
	// }
}

void AMyCharacter::ServerFire_Implementation(int32 Bullets, FVector ForwardVector)
{
	if(Bullets > 0 || IsPlayerControlled() == false)
	{
		AR->Bullet();
	}
	else if(CrossBow != nullptr)
	{
		//pass in info from the client to the server about the camera maybe.
		
		CrossBow->ArrowCalculations(ForwardVector, Camera->GetComponentLocation(), PlacementRotation);
		
	}
	// UE_LOG(LogTemp, Warning, TEXT("ammo %i"), Bullets)
	--Bullets;
	

}

void AMyCharacter::Fire()
{
	// else if (Isplayed)
	IsFireHeld = true;
	if(CrossBow != nullptr|| AR != nullptr)
	{
		if(!HasAuthority() && !IsReloading || IsPlayerControlled() == true)
		{
			
			ServerFire(BulletsInMag, Camera->GetForwardVector());

		}
	}

	if(BulletsInMag > 0 && IsAR)
	{
		
		if (!IsReloading || IsPlayerControlled() == false && AR != nullptr)
		{
			AmmoCalculations(this, AR);
		}
		else if(AR == nullptr)
		{
			//this will sometimes happen just means you have to reset what the gunclass is in the character bp or make sure the player is the client not standalone or server
			UE_LOG(LogTemp, Error, TEXT("AR == nullptr"))
		}
	}
	else
	{
		LeftClick();
	}
}

void AMyCharacter::FireReleased()
{
	// Since it's replicated all you got
	IsFireHeld = false;
}

void AMyCharacter::ServerLeftClick_Implementation()
{
	
	if(!GetWorldTimerManager().IsTimerActive(HatchetSwingDelay) && SwingAxe == false)
	{
		
		//to make them swing faster all you have to do is increase the playrate of the chop and then decrease the timer.
		GetWorldTimerManager().SetTimer(HatchetSwingDelay, this, &AMyCharacter::SwingAxeTimer, 1.6f, false);
		SwingAxe = true;
		
		Hatchet->ServerSwing(GetController(), this);
	}

}

void AMyCharacter::LeftClick()
{
	
	if (!IsAR && IsHatchet)
	{
		//if is fire is true set a timer that basically just runs serverleftclick until 
		
			if(!HasAuthority() && Hatchet != nullptr && GetWorldTimerManager().IsTimerActive(HatchetSwingDelay) == false)
			{
				ServerLeftClick();
				GetWorldTimerManager().SetTimer(HatchetSwingDelay, 1.65f, false);
			}
			else if(Hatchet != nullptr && GetWorldTimerManager().IsTimerActive(HatchetSwingDelay) != false)
			{
				UE_LOG(LogTemp, Error, TEXT("Hatchet == nullptr"))
			}	
	}
	else if (Handle->GetGrabbedComponent() != nullptr)
	{
		ReleaseDrop();
	}
	
}
	
void AMyCharacter::Reload()
{
	//this is never created on the client therefore it causes the game to crash when ran
	
	if (PlayerIsJumping == false && IsAR && AR != nullptr)
	{
		IsReloading = true;
		GetWorld()->GetTimerManager().SetTimer(FireRateDelay, this, &AMyCharacter::CanFire, ReloadRate, true);
		ReloadMagazine(this);
	}
	// else if(AR == nullptr)
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Reload AR == nullptr"))
	// }
}
void AMyCharacter::StartJump()
{
	//It may be time to switch over to using enums
	if (TurnOffCrouch == false && PlayerIsJumping == false && IsReloading == false)
	{
		GetWorld()->GetTimerManager().SetTimer(FireRateDelay, this, &AMyCharacter::JumpEndAnim, 1.6, false);
		PlayerIsJumping = true;
		bPressedJump = true;
		

	}
}

void AMyCharacter::ServerGrab_Implementation()
{
	Grab();
}
void AMyCharacter::ServerReleaseThrow_Implementation()
{
	ReleaseThrow();
}
void AMyCharacter::ServerReleaseDrop_Implementation()
{
	ReleaseDrop();
}
//Input Related to the GrabberSystem
void AMyCharacter::Grab()
{
	//find some way to reduce the length that cube is at
	if(!HasAuthority())
	{
		ServerGrab();
	}
	// if you really want to remove the bug with the block sliding when you attempt to grab, you could use a linetrace in order to check if a block is under you and then not allow them to pick stuff up
	if (IsAR == false && IsHatchet == false && AllowBuilding == false)
	{
		FVector GrabbingLocation;
		FRotator GrabRotation;

		GetController()->GetPlayerViewPoint(GrabbingLocation, GrabRotation);

		FVector GrabEnd = (GrabRotation.Vector() * 600 + GrabbingLocation);

		bool AxeHit = GetWorld()->LineTraceSingleByChannel(OutHit, GrabbingLocation, GrabEnd, ECC_Visibility, TraceParams);
		if (AxeHit)
		{
			if (OutHit.GetActor() && OutHit.GetComponent()->IsSimulatingPhysics() && Handle != nullptr)
			{
				Handle->GrabComponentAtLocation(OutHit.GetComponent(), FName("thumb_03_l"), OutHit.GetActor()->GetActorLocation() );
				IsGrabbing = true;
			}
		}
	}
}
void AMyCharacter::ServerGrabDetract_Implementation()
{
	GrabDetract();
}

void AMyCharacter::ServerGrabExtend_Implementation()
{
	GrabExtend();
}

void AMyCharacter::GrabExtend()
{
	if(!HasAuthority())
	{
		ServerGrabExtend();
	}
	if(GrabLength < 600)
	{
		GrabLength += 20;

	}
}
void AMyCharacter::GrabDetract()
{
	if(!HasAuthority())
	{
		ServerGrabDetract();
	}
	if(GrabLength > 160)
	{
		GrabLength -= 20;
	}
}

void AMyCharacter::ReleaseThrow()
{
	
	if(!HasAuthority())
	{
		ServerReleaseThrow();
	}
	if (Handle->GetGrabbedComponent() != nullptr)
	{
		Handle->GetGrabbedComponent()->SetPhysicsLinearVelocity(FVector(GetActorForwardVector().X * 1200, GetActorForwardVector().Y * 1200, 0));
	}
	Handle->ReleaseComponent();
	IsGrabbing = false;
}
void AMyCharacter::ReleaseDrop()
{
	if(!HasAuthority())
	{
		ServerReleaseDrop();
	}
	if (Handle->GetGrabbedComponent() != nullptr || AllowBuilding == true && Handle->GetGrabbedComponent() != nullptr)
	{
		Handle->GetGrabbedComponent()->SetPhysicsLinearVelocity(FVector(0, 0, 0));
		Handle->ReleaseComponent();
		IsGrabbing = false;
	}
}
//UI
//These 3 are UI Related
void AMyCharacter::ServerHealthPercentage_Implementation() const
{
	HealthPercentage();
}

float AMyCharacter::HealthPercentage() const
{
	if(!HasAuthority())
	{
		ServerHealthPercentage();
	}
	return (Health / 100.f);
}
int32 AMyCharacter::DisplayAmmo()
{
	return Ammo;
}
int32 AMyCharacter::DisplayMagazineAmmo()
{
	return BulletsInMag;
}

//ANIMATION
//These 4 are Anim Related
bool AMyCharacter::AnimationReload()
{
	//Small bug here when reloading the last amount of your ammo it won't do the animations
	if (IsReloading)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool AMyCharacter::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// bool AMyCharacter::StandToCrouch()
// {
// 	if(TurnOffCrouch)
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }

//ANIMATION
//These 2 ANIMATION toggle
// void AMyCharacter::Crouch()
// {
// 	if(StartCrouch && PlayerIsJumping == false)
// 	{
// 		IsCrouched = 0.5;
// 		TurnOffCrouch = true;
// 		PlayerCapsule->SetCapsuleSize(OutRadius, (OutHalfHeight + 30) /2 );
// 		GetMesh()->SetRelativeLocation(GetMesh()->GetRelativeLocation() + FVector(0, 0, 30));
// 	}
// 	StartCrouch = true;
// }

// void AMyCharacter::CrouchEnd()
// {
// 	if(TurnOffCrouch)
// 	{
// 		IsCrouched = 1;
// 		PlayerCapsule->SetCapsuleSize(OutRadius, OutHalfHeight);
// 		GetMesh()->SetRelativeLocation(GetMesh()->GetRelativeLocation() + FVector(0, 0, -30));
// 		StartCrouch = false;
// 		TurnOffCrouch = false;
// 	}
// }

void AMyCharacter::JumpEndAnim()
{
	PlayerIsJumping = false;
	bPressedJump = false;
}

//Other Logic
float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	
	int32 DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("here %i"), DamageApplied));
	if (IsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Destroy();
	}
	 	UE_LOG(LogTemp, Warning, TEXT("%i"), Health)
	return DamageApplied;
}

int32 AMyCharacter::FindPlayer()
{
	APlayerController *MainPlayer = Cast<APlayerController>(GetOwner());
	int32 PlayerID = UGameplayStatics::GetPlayerControllerID(MainPlayer);
	if (IsPlayerControlled())
	{
		return PlayerID;
	}
	else
	{
		return 0;
	}
}

void AMyCharacter::CanFire()
{
	IsReloading = false;
}

//maybe needs to be bool
void AMyCharacter::BP_CleanupBuild()
{
	if(!HasAuthority())
	{
		if(Floor != nullptr)
		{
			ServerCleanupBuild();
			
		}	
	}
	if(Floor != nullptr)
	{	
			
		Floor->Destroy();
		AllowBuilding = false;
		AllowedPlacement = false;
	}
}
//set for multiplayer from down here
void AMyCharacter::ServerCleanupBuild_Implementation()
{
	//use nullchecks
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s"), *MainActor->GetName()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%i"), FloorsArray.Num()));
	AllowBuilding = false;
	for(int32 i = 0; i < FloorsArray.Num(); i++)
	{
		FloorsLocations.Add(FloorsArray[i]->GetActorLocation());
		FloorsArray[i]->Destroy();
	}
	if(MainActor != nullptr)
	{
		MainActor->Destroy();
	}
		
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s"), *FloorsLocations[0].ToString()));
	
	//use for loop to get the locations of the array and then add it to an fvector array
	//then try destroying either the parent actor first and then if not try destroying all the attached actors

	//Spawn all the actors back in attaching them to the og parent actor, and set them to their og locations, then moving the owning actor towards the water or a dock
	//Simulate physics if something is it a linetrace is hitting the water and nothing is obstructing it.
	
}

//perfect for system with bp just needs to be called upon
void AMyCharacter::BP_FindPlacementLocation(int32 BuildingPiece)
{
	//input function ran off leftclick
	
	if(!HasAuthority())
	{	

		if(OutHit.GetActor() != nullptr && AllowedPlacement && AllowBuilding)
		{	
			//if building piece is == 1 and outhit is triangle then change building piece.
			if(BuildingPiece == 1 && OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[3].X)
			{
				BuildingPiece = 4;
			}
			ServerFindPlacementLocation(Floor->GetActorLocation(), Floor->GetActorRotation(), BuildingPiece, OutHit.GetActor(), LandScapeHit, IndexOfShortest, RoofLocation);
	
		}	

	}
}
void AMyCharacter::ServerFindPlacementLocation_Implementation(const FVector Client, const FRotator ClientRotation, const int32 BuildObjectNum,  AActor* FloorActor, const bool LandHit, const int32 ShortestIndex, const FVector RoofLoc)
{


	Floor = GetWorld()->SpawnActor<AFloor>(FloorClass);
	MulticastFindPlacementLocation(Client, ClientRotation, BuildObjectNum, ShortestIndex, LandHit, RoofLoc, FloorActor);
	if(LandHit)
	{
		MainActor = Floor;
		
		//Bug that has to do with landhit being activated when 

	}
	else if(!LandHit)
	{
		Floor->AttachToActor(FloorActor, FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false));
		
		ChildActors = Floor;
		FloorsArray.Add(ChildActors);

		//use for loop in order to get the world location and then check what it is cloest to on snap locations
		
		//
		
	}
	//really need to setup a linetrace for this but it's alright for now
	
}

void AMyCharacter::MulticastFindPlacementLocation_Implementation(const FVector Client, const FRotator ClientRotation, const int32 BuildObjectNum, const int32 ShortestIndex, const bool LandHit, const FVector RoofLoc, const AActor* FloorActor)
{
	//only works for the first block
	//perfect for land hit need to use info from buildkit in order to get the correct snap location for some of these relative one's however
	if(Floor != nullptr )
	{
		//landscape is hit
		if(BuildObjectNum < 5)
		{
			Floor->SetFloorShape(BuildObjectNum);
		}
		if(BuildObjectNum == 0 )
		{
			Floor->SetActorScale3D(BuildingTypes[BuildObjectNum] + FVector(0,0, 0.5));
			
		}
		else
		{
			Floor->SetActorScale3D(BuildingTypes[BuildObjectNum]);
		}
		
		Floor->SetActorRotation(ClientRotation);	
		Floor->SetActorLocation(Client);

		if(BuildObjectNum == 1 && FloorActor->GetActorScale3D().X == BuildingTypes[3].X)
		{
			
			Floor->SetActorScale3D(Floor->GetActorScale3D() - FVector(0, 0.2,0));
		}


	


	}
	
}

void AMyCharacter::BP_BuildMenu(int32 BuildingPiece)
{
	if(Floor != nullptr)
	{
		Floor->Destroy();
	}
	Floor = GetWorld()->SpawnActor<AFloor>(FloorClass);
	
	Floor->SetFloorShape(BuildingPiece);
	//needs to be modified to be variable

	Floor->SetActorScale3D(BuildingTypes[BuildingPiece]);
	Floor->Overlap(); //may cause issue
	AllowBuilding = true; 
	AllowedPlacement = false;
	
}
void AMyCharacter::BP_BuildKit(int32 BuildingPiece, int32& ExitBuildingPiece) 
{
	//BuildingPiece 0 is floors && roofs
	GetController()->GetPlayerViewPoint(Location, Rotation);
	End = (Location + Rotation.Vector() * 600);
	
	if(Floor != nullptr && AllowBuilding)
	{
		Floor->SetActorRotation(FRotator(0,0,0));
		TraceParams.AddIgnoredActor(Floor);

		bool BuildingSnap = GetWorld()->LineTraceSingleByChannel(OutHit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, TraceParams);
		if(BuildingSnap == false)
		{
			LandScapeHit = true;
			GetWorld()->LineTraceSingleByChannel(OutHit, Location, End, ECollisionChannel::ECC_GameTraceChannel2, TraceParams);
		}
		else
		{
			LandScapeHit = false;
		}


		if(OutHit.GetActor() == nullptr)
		{	
			if(Floor != nullptr)
			{
				Floor->SetActorLocation(End + FVector(0, 0, 50));
				Floor->MaterialRed();
			}
			AllowedPlacement = false;
		}
		else if(OutHit.GetActor() != nullptr)
		{
			
			if(BuildingSnap)
			{


			float ShortestDistance = FVector::Distance(End, FloorSnapLocation[0] + OutHit.GetActor()->GetActorLocation());
			float FloorToTriangleDistance = FVector::Distance(OutHit.TraceEnd, TriangleSnapLocation[0] + OutHit.GetActor()->GetActorLocation());
			float ShortestDistanceRoof = FVector::Distance(GetOwner()->GetActorLocation(), RoofSnapLocation[0] + OutHit.GetActor()->GetActorLocation());
			IndexOfShortest = 0;
			Index = 0;

			//don't try to use buildtype values that use floats as then it leads to the system getting bugged.
			if (BuildingPiece == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("in 0"))
				if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[0].X)
				{
					Index = 0;
					if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -30 )
					{
						Index = 4;
						Floor->SetActorRotation(FRotator(0, -29.9,0));
					}
					else if(FMath::RoundToPositiveInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == 30)
					{
						Index = 8;
						Floor->SetActorRotation(FRotator(0, 29.9,0));		
					}



					
					for(int32 MaxIndex = Index + 3; Index < FloorSnapLocation.Num() &&  Index <= MaxIndex; Index++)
					{
						if (FVector::Distance(LineTraceEnd, FloorSnapLocation[Index] + OutHit.GetActor()->GetActorLocation()) < ShortestDistance)
						{
							ShortestDistance = FVector::Distance(LineTraceEnd, FloorSnapLocation[Index] + OutHit.GetActor()->GetActorLocation());
							IndexOfShortest = Index;
						}
					}
					//UE_LOG(LogTemp, Warning, TEXT("%i"), IndexOfS)
				if(IndexOfShortest != 0 || IndexOfShortest == 0 && Index == 4)
				{
					Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation()  + FloorSnapLocation[IndexOfShortest]);
				}
					FVector FloorStart = Floor->GetActorLocation() + FVector(0,0, 60);
					bool FloorCheck = GetWorld()->LineTraceSingleByChannel(CubeHit, FloorStart, (FloorStart + FRotator(-90, 0,0).Vector() * 140), ECollisionChannel::ECC_GameTraceChannel2, TraceParams);

					if(FloorCheck)
					{
						AllowedPlacement = true;
						Floor->MaterialGreen();
					}
					else
					{
						AllowedPlacement = false;
						Floor->MaterialRed();
					}
					WallRotationValue = Floor->GetActorRotation();
				}
				else if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[3].X)
				{
					Index = 0;
					IndexOfShortest = 0;
					if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == 89.f)
					{
						Floor->SetActorRotation((FRotator(0, 180, 0)  + OutHit.GetActor()->GetActorRotation()));
						Index = 6;
					}
					else if (FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Roll) == -180.f && FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -90.f)
					{
						Index = 12;
					}
					else if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Roll) == -180.f)
					{
						Index = 0;
					}
					else if(FMath::RoundToPositiveInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == 0.f)
					{
						Index = 3;
					}
					else if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -90.f)
					{
			
						Index = 9;
					}
					for(int32 MaxIndex = Index + 2; Index < FloorToTriangleSnapLocation.Num() &&  Index <= MaxIndex; Index++)
					{

						if (FVector::Distance(LineTraceEnd, FloorToTriangleSnapLocation[Index] + OutHit.GetActor()->GetActorLocation()) < ShortestDistance)
						{
							//Should check first if it is closer then the third shortest distance.
							ShortestDistance = FVector::Distance(LineTraceEnd, FloorToTriangleSnapLocation[Index] + OutHit.GetActor()->GetActorLocation());
							IndexOfShortest = Index;
						}
					}	

						if(IndexOfShortest == 1 || IndexOfShortest == 3 || IndexOfShortest == 6 || IndexOfShortest == 10  || IndexOfShortest == 12 || IndexOfShortest == 15)
						{
							Floor->SetActorRotation( FRotator(0, 29.9, 0));
						}
						else if(IndexOfShortest == 0 || IndexOfShortest == 4 || IndexOfShortest == 7 ||  IndexOfShortest == 13 || IndexOfShortest == 9)
						{
							Floor->SetActorRotation(FRotator(0, -29.9, 0));
						}

					if(IndexOfShortest != 0 || IndexOfShortest == 0 && Index == 3)
					{
						Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation()  + FloorToTriangleSnapLocation[IndexOfShortest]);
						PreviousRotation = Floor->GetActorRotation();


						Floor->MaterialGreen();
						AllowedPlacement = true;

					}
					else
					{
						Floor->SetActorRotation(PreviousRotation);

						Floor->MaterialRed();
						AllowedPlacement = false;

					}
					WallRotationValue = Floor->GetActorRotation();
				}
				else
				{
					AllowedPlacement = false;
					Floor->MaterialRed();
				}
					
			}
			else if(BuildingPiece == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("in 1"))
				//Wall Snap


					if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[0].X)
					{
						//can specify a bit more here on what it's hitting as this outhit allows for two things
						for (int i = 1; i < WallSnapLocation.Num(); i++)
						{
							if (FVector::Distance(LineTraceEnd, WallSnapLocation[i] + OutHit.GetActor()->GetActorLocation()) < ShortestDistance)
							{
								ShortestDistance = FVector::Distance(LineTraceEnd, WallSnapLocation[i] + OutHit.GetActor()->GetActorLocation());
								IndexOfShortest = i;
							}
						}


						Floor->MaterialGreen();
						if(OutHit.GetActor()->GetActorScale3D().Z < 1)
						{
							Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation()  + WallSnapLocation[IndexOfShortest] +  FVector(0,0, 140));
						}
						else
						{
							Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation()  + WallSnapLocation[IndexOfShortest] +  FVector(0,0, 220));
						}
						
						if(IndexOfShortest == 2 || IndexOfShortest == 3) // can make this more accurate, by getting the direction it is at
						{
							Floor->SetActorRotation(FRotator(0, 90, 0) + OutHit.GetActor()->GetActorRotation());
							
						}
						else
						{
							Floor->SetActorRotation(FRotator(0, 0, 0) + OutHit.GetActor()->GetActorRotation());
							
						}
						AllowedPlacement = true;
					}
					else if(OutHit.GetActor()->GetActorScale3D().Z == BuildingTypes[1].Z)
					{
						for (int i = 1; i < WallSnapLocation.Num(); i++)
						{
							if (FVector::Distance(LineTraceEnd, WallSnapLocation[i] + OutHit.GetActor()->GetActorLocation()) < ShortestDistance)
							{
								ShortestDistance = FVector::Distance(LineTraceEnd, WallSnapLocation[i] + OutHit.GetActor()->GetActorLocation());
								IndexOfShortest = i;
							}
						}

						Floor->SetActorLocation(FVector(0, 0, 100) + OutHit.GetActor()->GetActorLocation());
						
						if(OutHit.GetActor()->GetActorRotation() == FRotator(0,330.1f,0))
						{
							Floor->SetActorRotation(FRotator(0, 90, 0) + OutHit.GetActor()->GetActorRotation());
						}
						else
						{
							Floor->SetActorRotation(FRotator(0,0,0) + OutHit.GetActor()->GetActorRotation());
						}
						Floor->MaterialGreen();
						AllowedPlacement = true;
					}	
					else if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[3].X)
					{
							BuildingPiece = 4;
							Floor->SetFloorShape(BuildingPiece);
							Floor->SetActorScale3D(BuildingTypes[BuildingPiece]);
							
					}
				WallRotationValue = Floor->GetActorRotation();	
			}
			else if(BuildingPiece == 2)
			{
				UE_LOG(LogTemp, Warning, TEXT("in 2"))
				if(OutHit.GetActor()->GetActorScale3D().Z == BuildingTypes[1].Z)
				{	
						
				
						if(OutHit.GetActor()->GetActorRotation() == FRotator(0,0,0))
						{
							if(this->GetActorLocation().X > OutHit.GetActor()->GetActorLocation().X)
							{
								Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation() + FVector(125, 0 , 160));
								RoofLocation = FVector(649.9f, -0.045 , 51);
							}
							else if(this->GetActorLocation().X < OutHit.GetActor()->GetActorLocation().X)
							{
								Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation() + FVector(-125, 0 , 160));
								RoofLocation =  FVector(-649.9f, -0.045 , 51);
								//
							}
						}
						else if(OutHit.GetActor()->GetActorRotation() != FRotator(0,0,0))
						{
							if(this->GetActorLocation().Y < OutHit.GetActor()->GetActorLocation().Y)
							{
								Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation() + FVector(0, -125 , 160));
								RoofLocation =  FVector(-649.9f, -0.045 , 51);
							}
							else if(this->GetActorLocation().Y > OutHit.GetActor()->GetActorLocation().Y)
							{
								Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation() + FVector(0, 125 , 160));
								RoofLocation = FVector(649.9f, -0.045 , 51);
							}
						}
						
						Floor->MaterialGreen();
						AllowedPlacement = true;					
				}
				else if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[2].X )
				{

					IndexOfShortest = 0;
					for (int i = 1; i < WallSnapLocation.Num(); i++)
					{
						if (FVector::Distance(LineTraceEnd, RoofSnapLocation[i] + OutHit.GetActor()->GetActorLocation()) < ShortestDistance)
						{
							ShortestDistance = FVector::Distance(LineTraceEnd, RoofSnapLocation[i] + OutHit.GetActor()->GetActorLocation());
							IndexOfShortest = i;
						}
					}
					Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation() + RoofSnapLocation[IndexOfShortest]);
					RoofLocation = RoofSnapLocation[IndexOfShortest];
					Floor->MaterialGreen();
					AllowedPlacement = true;	
				}
				WallRotationValue = Floor->GetActorRotation();	
				
			}
			else if(BuildingPiece == 3)
			{
				UE_LOG(LogTemp, Warning, TEXT("in 3"))
				if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[0].X)
				{
					Index = 0;
					
					if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -30.f)
					{
						Index = 4;
					}
					
					for (int32 MaxIndex = Index + 3; Index < FloorTriangleSnapLocation.Num() && Index <= MaxIndex; Index++)
					{
						if (FVector::Distance(LineTraceEnd, FloorTriangleSnapLocation[Index] + OutHit.GetActor()->GetActorLocation()) < ShortestDistance)
						{
							ShortestDistance = FVector::Distance(LineTraceEnd, FloorTriangleSnapLocation[Index] + OutHit.GetActor()->GetActorLocation());
							IndexOfShortest = Index;
						}
					}

						Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation()  + FloorTriangleSnapLocation[IndexOfShortest]);
					
					FVector FloorStart = Floor->GetActorLocation() + FVector(0,0, 60);
					bool FloorCheck = GetWorld()->LineTraceSingleByChannel(CubeHit, FloorStart, (FloorStart + FRotator(-90, 0,0).Vector() * 140), ECollisionChannel::ECC_GameTraceChannel2, TraceParams);
					
						if(IndexOfShortest == 0)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, -90, 0));
						}
						else if(IndexOfShortest == 1)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() +  FRotator(0, 90, 0));

						}
						else if(IndexOfShortest == 2)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, -60, 0));
						}
						else if(IndexOfShortest == 3)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation());
						}
						else if(IndexOfShortest == 4)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, -90, 0));
						}
						else if(IndexOfShortest == 5)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, 90, 0));
						}
						else if(IndexOfShortest == 6)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, -60, 0));
						}
						else if(IndexOfShortest == 7)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation());
						}

					if(FloorCheck)
					{
						AllowedPlacement = true;
						Floor->MaterialGreen();
					}
					else
					{
						AllowedPlacement = false;
						Floor->MaterialRed();
					}
					
						
				}
				else if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[3].X)
				{
					
					if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == 89.f)
					{
						Floor->SetActorRotation((FRotator(0, 180, 0)  + OutHit.GetActor()->GetActorRotation()));
						Index = 6;
					}
					else if (FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Roll) == -180.f && FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -90.f)
					{
						Floor->SetActorRotation((FRotator(0, 0, -180)  + OutHit.GetActor()->GetActorRotation()));
						Index = 12;
					}
					else if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Roll) == -180.f)
					{
						Floor->SetActorRotation((FRotator(0, 0, -180)  + OutHit.GetActor()->GetActorRotation()));
						Index = 0;
					}
					else if(FMath::RoundToPositiveInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == 0.f)
					{
						Floor->SetActorRotation((FRotator(0, 0, -180)  + OutHit.GetActor()->GetActorRotation()));
						Index = 3;
					}
					else if(FMath::RoundToNegativeInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -90.f)
					{
						Floor->SetActorRotation((FRotator(0, 0, -180)  + OutHit.GetActor()->GetActorRotation()));
						Index = 9;
					}
					
						
					for(int32 MaxIndex = Index + 2; Index < TriangleSnapLocation.Num() &&  Index <= MaxIndex; Index++)
					{

						if (FVector::Distance(LineTraceEnd, TriangleSnapLocation[Index] + OutHit.GetActor()->GetActorLocation()) < ShortestDistance)
						{
							//Should check first if it is closer then the third shortest distance.
							ShortestDistance = FVector::Distance(LineTraceEnd, TriangleSnapLocation[Index] + OutHit.GetActor()->GetActorLocation());
							IndexOfShortest = Index;
						}
					}	
					UE_LOG(LogTemp, Warning, TEXT("%i"), IndexOfShortest)
					//need to the the rotation based off index somewhere overhere.
					if(IndexOfShortest != 0 && (Index != 12 || Index != 9 || Index != 6 || Index != 15) || IndexOfShortest == 0 && Index == 3)
					{
						PreviousRotation = Floor->GetActorRotation();
						Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation()  + TriangleSnapLocation[IndexOfShortest]);
						Floor->MaterialGreen();
						AllowedPlacement = true;
					}
					else
					{
						Floor->SetActorRotation(PreviousRotation);
						Floor->MaterialRed();
						AllowedPlacement = false;
					}

					//need to make sure it doesn't go under three
					
					// Instead of this can just get the closest one to it.

					//Need to make a new for loop that cycles through all of the possible locations instead and then picks three of them to be used.
					//Actually doing that may not work as the closest location might not always be the correct location so likely just add new values to array.

					// if not you need to figure out the new values for some of the angles to add to array
					
				}			
				WallRotationValue = Floor->GetActorRotation();
			}
			else if(BuildingPiece == 4)
			{
				UE_LOG(LogTemp, Warning, TEXT("in 4"))
				if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[3].X)
				{
					
						if(FMath::RoundToPositiveInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -60)
						{
							IndexOfShortest = 3;
							Index = 3;
						}
						else if(FMath::RoundToPositiveInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == -89)
						{
							IndexOfShortest = 5;
							Index = 5;
						}
						else if(FMath::RoundToPositiveInfinity(OutHit.GetActor()->GetActorRotation().Yaw) == 90)
						{
							IndexOfShortest = 7;
							Index = 7;
						}
						else
						{
							Index = 0;
						}
						float ShortestDistanceWall = FVector::Distance(LineTraceEnd, TriangleWallSnapLocation[Index] + OutHit.GetActor()->GetActorLocation());

						//If the index is not set for shortest distance it starts out with an index of 0
						for (int32 MaxIndex = Index + 2; Index < TriangleWallSnapLocation.Num() &&  Index <= MaxIndex; Index++)
						{
							if (FVector::Distance(LineTraceEnd, TriangleWallSnapLocation[Index] + OutHit.GetActor()->GetActorLocation()) < ShortestDistanceWall)
							{
								ShortestDistanceWall = FVector::Distance(LineTraceEnd, TriangleWallSnapLocation[Index] + OutHit.GetActor()->GetActorLocation());
								IndexOfShortest = Index;
							}

						}

						if( IndexOfShortest == 3 || IndexOfShortest == 8 )
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, -150,0));
						}
						else if(IndexOfShortest == 6 || IndexOfShortest == 0 || IndexOfShortest == 4 || IndexOfShortest == 7)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, -30,0));
						}
						else if( IndexOfShortest == 5 || IndexOfShortest == 9)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, 90,0));
						}
						else if(IndexOfShortest == 2 )
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, -270 ,0));
						}
						else if(IndexOfShortest == 1)
						{
							Floor->SetActorRotation(OutHit.GetActor()->GetActorRotation() + FRotator(0, 210 ,0));
						}
                        UE_LOG(LogTemp, Warning, TEXT(" index of shortest %i"), IndexOfShortest)

						Floor->SetActorLocation(OutHit.GetActor()->GetActorLocation() + TriangleWallSnapLocation[IndexOfShortest]);
						Floor->MaterialGreen();
						AllowedPlacement = true;
				}
				else if(OutHit.GetActor()->GetActorScale3D().X == BuildingTypes[0].X)
				{
					BuildingPiece = 1;
					Floor->SetFloorShape(BuildingPiece);
					Floor->SetActorScale3D(BuildingTypes[BuildingPiece]);
				}
				else
				{
					AllowedPlacement = true;
					Floor->MaterialRed();
					Floor->SetActorLocation(End);
					
				}
			}
			else
			{
				AllowedPlacement = false;
				Floor->MaterialRed();
			}
			
			}
			else if (!BuildingSnap)
			{
				Floor->SetActorLocation(End + FVector(0, 0, 50));
				Floor->MaterialRed();
				AllowedPlacement = false;

				Floor->SetActorRotation(WallRotationValue);
				if((BuildingPiece == 0 || BuildingPiece == 3) && LandScapeHit )
				{
					bool FloorCheck = GetWorld()->LineTraceSingleByChannel(CubeHit, Floor->GetActorLocation() + FVector(0, 0, 35), (Floor->GetActorLocation() + FVector(0, 0, 35) + FRotator(-90, 0,0).Vector() * 140), ECollisionChannel::ECC_GameTraceChannel2, TraceParams);
					Floor->SetActorRotation(FRotator(0,0,0));
					if (FloorCheck)
					{
					
							FVector CubeStart = Floor->GetActorLocation() - FVector(0,0, 15);
							//try ecc visibility may help from buildings overlapping
							bool CubeTrace1 = GetWorld()->LineTraceSingleByChannel(CubeHit, CubeStart, (CubeStart + FRotator(0, 135,0).Vector() * 300), ECollisionChannel::ECC_GameTraceChannel1, TraceParams);
							bool CubeTrace2 = GetWorld()->LineTraceSingleByChannel(CubeHit, CubeStart, (CubeStart + FRotator(0, 45,0).Vector() * 300), ECollisionChannel::ECC_GameTraceChannel1, TraceParams);
							bool CubeTrace3 = GetWorld()->LineTraceSingleByChannel(CubeHit, CubeStart, (CubeStart + FRotator(0, -135,0).Vector() * 300), ECollisionChannel::ECC_GameTraceChannel1, TraceParams);
							bool CubeTrace4 = GetWorld()->LineTraceSingleByChannel(CubeHit, CubeStart, (CubeStart + FRotator(0, -45,0).Vector() * 300), ECollisionChannel::ECC_GameTraceChannel1, TraceParams);

						if(CubeTrace1 || CubeTrace2 || CubeTrace3 || CubeTrace4)
						{	
							Floor->MaterialRed();
							AllowedPlacement = false;
						}
						else
						{
							Floor->MaterialGreen();
							AllowedPlacement = true;
						}
						
					}
					
				}

			}
			
		}
	}
    ExitBuildingPiece = BuildingPiece;
}
//
void AMyCharacter::ServerSwitchUp_Implementation(int32 BuildingPiece)
{
	//probably gonna need this to bp
	if(BuildingPiece == 4)
	{
		BuildingPiece = 1;
	}

	if(BuildingPiece < 3)
	{
		
		++BuildingPiece;
	}
	BP_SwitchUp(BuildingPiece);
	
}
int32 AMyCharacter::BP_SwitchUp(int32 BuildingPiece)
{	
	if(!HasAuthority())
	{
		ServerSwitchUp(BuildingPiece);
	}
	
	if(BuildingPiece == 4)
	{
		BuildingPiece = 1;
		UE_LOG(LogTemp, Warning, TEXT("here"))
	}

	if (AllowBuilding && BuildingPiece < 3)
	{

		++BuildingPiece;
		UE_LOG(LogTemp, Warning, TEXT("%i"), BuildingPiece)
		Floor->SetFloorShape(BuildingPiece);
		Floor->SetActorScale3D(BuildingTypes[BuildingPiece]);
		AllowedPlacement = false;
		Floor->MaterialRed();
		
		return BuildingPiece;
	}
	return BuildingPiece;
}

void AMyCharacter::ServerSwitchDown_Implementation(int32 BuildingPiece)
{
	if(BuildingPiece == 4)
	{
		BuildingPiece = 1;
	}
	if(BuildingPiece >= 1)
	{
		--BuildingPiece;
	}
	BP_SwitchDown(BuildingPiece);
}
int32 AMyCharacter::BP_SwitchDown(int32 BuildingPiece)
{
	if(!HasAuthority())
	{
		ServerSwitchDown(BuildingPiece);
	}
	
	if(BuildingPiece == 4)
	{
		BuildingPiece = 1;
		UE_LOG(LogTemp, Warning, TEXT("here"))
	}

	if (AllowBuilding && BuildingPiece >= 1)
	{
		--BuildingPiece;

		Floor->SetFloorShape(BuildingPiece);
		Floor->SetActorScale3D(BuildingTypes[BuildingPiece]);
		AllowedPlacement = false;
		Floor->MaterialRed();

		return BuildingPiece;
	}
	return BuildingPiece;
}


//interaction system from rueban ward tutorial
void AMyCharacter::PerformInteractionCheck()
{
	if(GetController() == nullptr){return;}
	FVector EyesLoc;
	FRotator EyesRot;

	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	
	GetController()->GetPlayerViewPoint(EyesLoc, EyesRot);

	FVector TraceStart = EyesLoc;
	FVector TraceEnd = ((EyesRot.Vector()* InteractionCheckDistance) + TraceStart);
	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if(GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if(TraceHit.GetActor())
		{
			if(UInteractionComponent* InteractionComponent = Cast<UInteractionComponent>(TraceHit.GetActor()->GetComponentByClass(UInteractionComponent::StaticClass())))
			{
				float Distance = (TraceStart - TraceHit.ImpactPoint).Size();

				if(InteractionComponent != GetInteractable() && Distance <= InteractionComponent->InteractionDistance)
				{
					FoundNewInteractable(InteractionComponent);
				}
				else if(Distance > InteractionComponent->InteractionDistance && GetInteractable())
				{
					CouldntFindInteractable();
				}
				return;
			}
		}
	}
	CouldntFindInteractable();
}
void AMyCharacter::FoundNewInteractable(UInteractionComponent * Interactable)
{
	EndInteract();

	if(UInteractionComponent* OldInteractable = GetInteractable())
	{
		OldInteractable->EndFocus(this);
	}
	InteractionData.ViewedInteractionComponent = Interactable;
	Interactable->BeginFocus(this);
}
void AMyCharacter::CouldntFindInteractable()
{
	if(GetWorldTimerManager().IsTimerActive(TimerHandle_Interact))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	}

	if(UInteractionComponent* Interactable = GetInteractable())
	{
		Interactable->EndFocus(this);

		if(InteractionData.bInteractionHeld)
		{
			EndInteract();
		}
	}

	InteractionData.ViewedInteractionComponent = nullptr;
}

void AMyCharacter::BeginInteract()
{
	if(!HasAuthority())
	{
		ServerBeginInteract();
	}
	
	InteractionData.bInteractionHeld = true;
	if(UInteractionComponent * Interactable = GetInteractable())
	{
		Interactable->BeginInteract(this);

		if(FMath::IsNearlyZero(Interactable->InteractionTime))
		{
			Interact();
		}
		else
		{
			GetWorldTimerManager().SetTimer(TimerHandle_Interact, this, &AMyCharacter::Interact, Interactable->InteractionTime, false);
		}
	}
}

void AMyCharacter::EndInteract()
{
	if(!HasAuthority())
	{
		ServerBeginInteract();
	}
	InteractionData.bInteractionHeld = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	
	if(UInteractionComponent * Interactable = GetInteractable())
	{
		Interactable->EndInteract(this);
	}
}

void AMyCharacter::ServerBeginInteract_Implementation()
{
	BeginInteract();
}
bool AMyCharacter::ServerBeginInteract_Validate()
{
	return true;
}

void AMyCharacter::ServerEndInteract_Implementation()
{
	BeginInteract();
}
bool AMyCharacter::ServerEndInteract_Validate()
{
	return true;
}

void AMyCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyInter"))
	GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	
	if(UInteractionComponent * Interactable = GetInteractable())
	{
		Interactable->Interact(this);
	}
}

bool AMyCharacter::IsInteracting() const
{
	return GetWorldTimerManager().IsTimerActive(TimerHandle_Interact);
}

float AMyCharacter::GetRemainingInteractTime() const
{
	return GetWorldTimerManager().GetTimerRemaining(TimerHandle_Interact);
}

void AMyCharacter::SwingAxeTimer()
{
	SwingAxe = false;
}

