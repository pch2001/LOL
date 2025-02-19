// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	collisionComp->SetSphereRadius(13.f);
	collisionComp->SetNotifyRigidBodyCollision(true);
	collisionComp->SetSimulatePhysics(true); // 물리 시뮬레이션 활성화
	collisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	RootComponent = collisionComp;

	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp->SetupAttachment(collisionComp);
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movementComp->SetUpdatedComponent(collisionComp);
	movementComp->InitialSpeed = 3000.f;
	movementComp->MaxSpeed = 3000.f;
	movementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 2.f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	 
	Super::BeginPlay();


	FVector ForwardVector = GetActorForwardVector();
	movementComp->Velocity = ForwardVector * movementComp->InitialSpeed;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void ABullet::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
) {
	

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		// 충돌한 액터가 Enemy 클래스인지 확인
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);

		if (Enemy)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, Hit.ImpactPoint, Hit.ImpactNormal.Rotation() );

			UEnemyFSM* EnemyFSM = Enemy->FindComponentByClass<UEnemyFSM>();
			EnemyFSM->OnDamageProcess(BulletPower);
			Destroy();

		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("No enemy!"));

		}
	}

}