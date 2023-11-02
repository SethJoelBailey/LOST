// Fill out your copyright notice in the Description page of Project Settings.


#include "Canon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACanon::ACanon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

}

void ACanon::OnConstruction(const FTransform& Transform)
{
	if (MeshAsset != nullptr) MeshComponent->SetStaticMesh(MeshAsset);
}

// Called when the game starts or when spawned
void ACanon::BeginPlay()
{
	Super::BeginPlay();

	if (MeshAsset) MeshComponent->SetStaticMesh(MeshAsset);
	
	PlayerRef = Cast<ACharacter>(UGameplayStatics::GetActorOfClass(this, ACharacter::StaticClass()));

	if (!PlayerRef) Destroy();

	FTimerDelegate TurnDelegate;
	TurnDelegate.BindUFunction(this, FName("TurnToPlayer"));
	GetWorld()->GetTimerManager().SetTimer(TurnTimer, TurnDelegate, GetWorld()->GetDeltaSeconds(), true);
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, "Turn timer set");
}

void ACanon::TurnToPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, "Turning");
	FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerRef->GetActorLocation());
	SetActorRotation(NewRot);
}

// Called every frame
void ACanon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

