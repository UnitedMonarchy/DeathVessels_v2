// Copyright Jonathan Bejarano, DeathVessels C++

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstance.h"
#include "Floor.generated.h"

class AAssaultRifle;
class AHatchet;
class UMaterialInterface;
UCLASS()
class DEATHVESSELS_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

	void SetFloorShape(int32 BuildingNum);

	void OverlapTrace();
	void BlockTrace();

	void FloorOverlap();
	void Overlap();

	void BlockDisplay();
	void OverlapDisplay();
	void MaterialRed();
	void MaterialGreen();
	void Block();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FloorBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	UStaticMesh* Triangle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	UStaticMesh* TriangleWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	UStaticMesh* Floor;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	UStaticMesh* Cube;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float FloorHealth = 100;

	int32 Number = 0;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* Green;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* Red;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* Original;


};
