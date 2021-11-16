// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
 	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default values
	armLenght = 300.0f;
	rotationRate = FRotator(0, 500.0f, 0);
	
	// Camera Arm (Boom)
	cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));  // Add component
	cameraArm->SetupAttachment(RootComponent);                                   // Attach to "RootComponent"
	cameraArm->TargetArmLength = armLenght;	                                     // Set length
	cameraArm->bUsePawnControlRotation = true;                                   // Enable pawn controlled rotation
	
	// Camera
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));           // Add component
	camera->SetupAttachment(cameraArm, USpringArmComponent::SocketName);         // Attach to "cameraBoom" (at the end of the spring arm)
	camera->bUsePawnControlRotation = false;                                     // Disable pawn controlled rotation
	
	// Disable mesh rotation
	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;
	
	// Change mesh by movement input
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = rotationRate;
}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("LookX", this, &ATPCharacter::LookX);
	PlayerInputComponent->BindAxis("LookY", this, &ATPCharacter::LookY);
	PlayerInputComponent->BindAxis("MoveX", this, &ATPCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ATPCharacter::MoveY);
}

void ATPCharacter::LookX(float val)
{
	AddControllerYawInput(val * (45.0f * GetWorld()->GetDeltaSeconds()));
}

void ATPCharacter::LookY(float val)
{
	AddControllerPitchInput(val * (45.0f * GetWorld()->GetDeltaSeconds()));
}

void ATPCharacter::MoveX(float val)
{
	if (Controller == nullptr || val == 0.0f) return;
	
	const FRotator rotation = Controller->GetControlRotation();		// Returns controller rotation
	const FRotator yaw = FRotator(0, rotation.Yaw, 0);	// Save yaw rotation
	const FVector dir = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y); // Get direction (normalized)
	
	// Apply movement
	AddMovementInput(dir, val);
}

void ATPCharacter::MoveY(float val)
{
	if (Controller == nullptr || val == 0.0f) return;
	
	const FRotator rotation = Controller->GetControlRotation();		// Returns controller rotation
	const FRotator yaw = FRotator(0, rotation.Yaw, 0);	// Save yaw rotation
	const FVector dir = FRotationMatrix(yaw).GetUnitAxis(EAxis::X); // Get direction (normalized)
	
	// Apply movement
	AddMovementInput(dir, val);
}