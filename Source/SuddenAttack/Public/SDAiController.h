// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "SDAiController.generated.h"

/**
 * 
 */
UCLASS()
class SUDDENATTACK_API ASDAiController : public AAIController
{
	GENERATED_BODY()

public:
	ASDAiController(FObjectInitializer const& object_initilizer);
	void BeginPlay() override;
	void OnPossess(APawn* InPawn) override;

	class UBlackboardComponent* get_blackboard() const;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
		class UBehaviorTreeComponent* behaiver_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* btree;

private:

	class UBlackboardComponent* blackboard;
	class UAISenseConfig_Sight* SightConfig;

public:
	static const FName PosKey;
	static const FName TargetLocation;

	UFUNCTION()
	void OnUpdated(TArray<AActor*> const & updated_actors);
	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);
	UFUNCTION()
	void SetPerceptionSystem();

	//ai perception 변수 설정
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AiSightRadius = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AiLoseSightRadius = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AiFieldOfView = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AiSightAge = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AiLastSeenLocation = 900.f;
	
};
