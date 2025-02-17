// Copyright Jonathan Bejarano, DeathVessels C++

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyCharacter.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEATHVESSELS_API UInventoryTest : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryTest();

	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void ServerAddAmmo(class AMyCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void ItemAdjustment_BP(class AMyCharacter* Player, UStaticMeshComponent* ItemMesh, UInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintCallable)
	void CreateItemWidget(int32& ItemsInInventory);

	UFUNCTION(Server, Unreliable)
	void ServerArrayReduction(int32 Index);

	UFUNCTION(BlueprintCallable)
	void ItemInfo(class AMyCharacter* Player, int32& Amount, FString& Title, FString& Description);
	//class AMyCharacter* Player;
	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void ServerDropItem(class AMyCharacter* Player, int32 AmountToRemove, const FString& ItemToDrop);

	UFUNCTION(BlueprintCallable)
	float AmountToRemove(class AMyCharacter* Player, float ValueToRemove, float Amount);

	UPROPERTY(BlueprintReadWrite)
	bool AddToInventory;

	UPROPERTY(EditAnywhere, Category = "Items")
	UStaticMesh* Ammo;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Called every frame
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> AmmoModelClass;

	UPROPERTY(Replicated)
	bool ValueSet;

	UPROPERTY(Replicated)	
	TArray<FString> ItemName;
	
	UPROPERTY(Replicated)
	TArray<FString> ItemDescription;
	
	UPROPERTY(Replicated)
	TArray<int32> ItemNum;

	AActor* ItemModel;

	FString ItemTypeName;

	int32 ItemIndex = 0;

	int32 ItemTypeIndex = 0;

	int32 RandomNum;
};
