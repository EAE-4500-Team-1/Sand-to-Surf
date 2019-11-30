// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimGraphNode_DragonHandSolver.h"

#include "AnimationGraphSchema.h"


UAnimGraphNode_DragonHandSolver::UAnimGraphNode_DragonHandSolver(const FObjectInitializer & ObjectInitializer)
{
}



void UAnimGraphNode_DragonHandSolver::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("Pose"));
}






void UAnimGraphNode_DragonHandSolver::Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent * PreviewSkelMeshComp) const
{
	if (PreviewSkelMeshComp)
	{
		if (FAnimNode_DragonHandSolver* ActiveNode = GetActiveInstanceNode<FAnimNode_DragonHandSolver>(PreviewSkelMeshComp->GetAnimInstance()))
		{
			ActiveNode->ConditionalDebugDraw(PDI, PreviewSkelMeshComp);
		}
	}
}



FText UAnimGraphNode_DragonHandSolver::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(FString("Dragon Hand Solver"));
}

FText UAnimGraphNode_DragonHandSolver::GetTooltipText() const
{
	return FText::FromString(FString("Responsible for handling hand ik and full body solver"));
}

FString UAnimGraphNode_DragonHandSolver::GetNodeCategory() const
{
	return FString("Dragon.IK Plugin");
}

FLinearColor UAnimGraphNode_DragonHandSolver::GetNodeTitleColor() const
{
	return FLinearColor(10.0f / 255.0f, 127.0f / 255.0f, 248.0f / 255.0f);
}
