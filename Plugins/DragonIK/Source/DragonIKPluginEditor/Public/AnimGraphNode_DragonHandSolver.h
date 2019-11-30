// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"

#include "AnimNode_DragonHandSolver.h"

#include "AnimGraphNode_DragonHandSolver.generated.h"


class FPrimitiveDrawInterface;

/**
 * 
 */
UCLASS()
class DRAGONIKPLUGINEDITOR_API UAnimGraphNode_DragonHandSolver : public UAnimGraphNode_Base
{
	
	GENERATED_BODY()

	 UPROPERTY(EditAnywhere, Category = Settings)
		FAnimNode_DragonHandSolver ik_node;
	  public:
		  UAnimGraphNode_DragonHandSolver(const FObjectInitializer& ObjectInitializer);

		virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent * PreviewSkelMeshComp) const override;


		virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
		virtual FText GetTooltipText() const override;
		virtual FString GetNodeCategory() const override;
		virtual FLinearColor GetNodeTitleColor() const override;
		//	virtual FText GetControllerDescription() const override;

		virtual void CreateOutputPins() override;

};
