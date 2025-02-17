// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inventory.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MyInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyCharacter.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData()
	{
		ViewedInteractionComponent = nullptr;
		LastInteractionCheckTime = 0;
		bInteractionHeld = false;
	}

	UPROPERTY()
	class UInteractionComponent* ViewedInteractionComponent;

	UPROPERTY()
	float LastInteractionCheckTime;

	UPROPERTY()
	bool bInteractionHeld;
};

class AAssaultRifle;
class ACrossbow;
class AHatchet;
class AFloor;
class UPhysicsHandleComponent;

UCLASS()
class DEATHVESSELS_API AMyCharacter : public ACharacter, public IMyInterface
{
	GENERATED_BODY()

public:	
//building
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	//virtual void InteractPure() override;

	void ArrayValues();

	UFUNCTION(BlueprintCallable)
	void BP_FindPlacementLocation(int32 BuildingPiece);

	UFUNCTION(BlueprintCallable)
	void BP_CleanupBuild();

	UFUNCTION(BlueprintCallable)
	void BP_BuildKit(int32 BuildingPiece, int32& ExitBuildingPiece);

	UFUNCTION(BlueprintCallable)
	void BP_BuildMenu(int32 BuildingPiece);

	UFUNCTION(BlueprintCallable)
	int32 BP_SwitchUp(int32 BuildingPiece);

	UFUNCTION(BlueprintCallable)
	int32 BP_SwitchDown(int32 BuildingPiece);


	AMyCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const &DamageEvent,class AController * EventInstigator, AActor * DamageCauser) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config, Replicated)
	float WalkSpeed = 0.6;

	UPROPERTY(Replicated, BlueprintReadWrite)
	float YInput;
	
	UPROPERTY(Replicated, BlueprintReadWrite)
	float XInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config, Replicated)
	int32 Health;

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool SwingAxe = false;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool IsCrossBow = false;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool IsAR = false;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool IsHatchet = false;

	UPROPERTY(Replicated)
	AAssaultRifle* AR;
	
	UPROPERTY(Replicated)
	AHatchet* Hatchet;

	UPROPERTY(Replicated)
	ACrossbow* CrossBow;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// UFUNCTION(BlueprintCallable)
	// bool IsJumping();
	
	UFUNCTION(BlueprintPure, Category = "Health")
	float HealthPercentage() const;
	
	UFUNCTION(BlueprintCallable)
	int32 DisplayAmmo();

	UFUNCTION(BlueprintCallable)
	int32 DisplayMagazineAmmo();

	UFUNCTION(BlueprintCallable)
	int32 FindPlayer();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	class UInventoryTest* InventoryTest;
	
//inventory variables
	int32 Ammo = 0;
	bool RefreshInventory = true;
	int32 BulletsInMag;

	UPROPERTY(Replicated)
	int32 Wood = 0;

//Left click related
	UFUNCTION(Server, Unreliable)
	void ServerLeftClick();

	void LeftClick();

	void Fire();

	void FireReleased();

	bool IsFireHeld = false;

//other
	UFUNCTION(BlueprintCallable)
	bool AnimationReload();

	FHitResult OutHit;
	FHitResult CubeHit;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHatchet> HatchetClass;

	FVector LineTraceEnd;
//interaction

	bool IsInteracting() const;

	float GetRemainingInteractTime() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle FireRateDelay;

	FTimerHandle HatchetSwingDelay;
private:
//InputRelated
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Unreliable)
	void ServerFire(int32 Bullets, FVector ForwardVector);
	
	UFUNCTION(Server, Unreliable)
	void ServerHealthPercentage() const;

	void SwingAxeTimer();

	void YMovement(float AxisValue);
	void XMovement(float AxisValue);
	void Sprint();
	void SprintRelease();
	
	UFUNCTION(Server, Unreliable)
	void ServerYMovement(float AxisValue);

	UFUNCTION(Server, Unreliable)
	void ServerXMovement(float AxisValue);

	UFUNCTION(Server, Unreliable)
	void ServerSprint();

	UFUNCTION(Server, Unreliable)
	void ServerSprintRelease();

	void Reload();
	
	void StartJump();
	void JumpEndAnim();

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void ServerPlayerToolbar(const FKey Key, const FString& ToolName);

	UFUNCTION(Server, Unreliable)
	void ServerGrab();

	UFUNCTION(Server, Unreliable)
	void ServerReleaseThrow();

	UFUNCTION(Server, Unreliable)
	void ServerReleaseDrop();

	void Grab();
	void ReleaseThrow();
	void ReleaseDrop();
	
	UFUNCTION(Server, Unreliable)
	void ServerGrabExtend();

	UFUNCTION(Server, Unreliable)
	void ServerGrabDetract();

	void GrabDetract();
	void GrabExtend();

//building system

	FVector Location;
	FRotator Rotation; 
	FVector End;


	int32 IndexOfShortest;
	int32 Index;
	FRotator PreviousRotation;
	FRotator WallRotationValue;
	TArray<FVector> BuildingTypes;

	TArray<FVector> RoofSnapLocation;
	TArray<FVector> FloorSnapLocation;
	TArray<FVector> FloorSnapLocation30;
	TArray<FVector> WallSnapLocation;
	TArray<FVector> TriangleWallSnapLocation;
	TArray<FVector> FloorTriangleSnapLocation;
	TArray<FVector> TriangleSnapLocation;
	TArray<FVector> FloorToTriangleSnapLocation;

	TArray<FVector> FloorSnapConversions;
	TArray<FVector>	WallSnapConversion;
	TArray<FVector> TriangleWallSnapConversion;
	TArray<FVector> FloorSnapConversion30;
	TArray<FVector> RoofSnapConversion;
	TArray<FVector>	FloorTriangleSnapConversion;
	TArray<FVector> TriangleSnapConversion;
	TArray<FVector> FloorToTriangleSnapConversion;
	
	FVector RoofLocation;

	TArray<FVector> CubeSnapLocations;
	
	TArray<AActor*> FloorsArray;

	TArray<FVector> FloorsLocations;

	AActor* MainActor;
	AActor* ChildActors;

	UFUNCTION(Server, Unreliable)
	void ServerSwitchUp(int32 BuildingPiece);

	UFUNCTION(Server, Unreliable)
	void ServerSwitchDown(int32 BuildingPiece);

	UFUNCTION(Server, Reliable)
	void ServerCleanupBuild();

	UFUNCTION(Server, Reliable)
	void ServerFindPlacementLocation(const FVector Client, const FRotator ClientRotation, const int32 BuildObjectNum,  AActor* FloorActor, const bool LandHit, const int32 ShortestIndex, const FVector RoofLoc);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastFindPlacementLocation(const FVector Client, const FRotator ClientRotation, const int32 BuildObjectNum, const int32 ShortestIndex, const bool LandHit, const FVector RoofLoc, const AActor* FloorActor);


//other	
	float OutRadius;
	float OutHalfHeight;
	float IsCrouched = 1;	

	bool AlreadyPressed1 = false;
	bool AlreadyPressed2 = false;
	bool PlayerIsJumping;
	bool TurnOffCrouch;
	bool StartCrouch = true;

	bool IsGrabbing = false;
	bool AllowedPlacement = false;
	
	int32 ValueIncreaser = 1;
	int32 z = 0;
	int32 GrabLength = 120;
	int32 CubeIncreaser = 0;

	FVector LengthOfGrabber;

	FVector ClientLocation;
	FVector PlacementLocation;
	FRotator PlacementRotation;
	
	FCollisionQueryParams TraceParams;

	UCapsuleComponent* PlayerCapsule;
	AFloor* Floor;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* GrabLocation;

	UPROPERTY(EditAnywhere)
	class UPhysicsHandleComponent* Handle;



	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	bool LandScapeHit;

	bool IsReloading = false;

	bool AllowBuilding = false;

	void MayReload();
	void CanFire();

	UPROPERTY(EditAnywhere, Category = "Config")
	USoundBase* Waves;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAssaultRifle> GunClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACrossbow> CrossBowClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFloor> FloorClass;
	
	UPROPERTY(EditAnywhere, Category = "Health")
	int32 MaxHealth = 100;
	
	UPROPERTY(EditAnywhere, Category = "Ammo")
	float ReloadRate = 2;

//Interactable setup
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckFrequency;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionCheckDistance;

	void PerformInteractionCheck();

	void CouldntFindInteractable();

	void FoundNewInteractable(UInteractionComponent * Interactable);

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerBeginInteract();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerEndInteract();

	void Interact();

	void BeginInteract();
	void EndInteract();
	
	FTimerHandle TimerHandle_Interact;

	UPROPERTY()
	FInteractionData InteractionData;

	FORCEINLINE class UInteractionComponent* GetInteractable() const {return InteractionData.ViewedInteractionComponent;}
	
};