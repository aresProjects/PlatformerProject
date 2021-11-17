// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

UCLASS()
class PLATFORMERPROJECT_API ATPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	float ArmLenght;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator RotationRate;
	
	// Camera arm (boom) using SpringArm Component
	// Moves the camera close to the target whenever there's a collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* CameraArm;
	
	// Camera Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void LookX(float Val);
	void LookY(float Val);
	void MoveX(float Val);
	void MoveY(float Val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};