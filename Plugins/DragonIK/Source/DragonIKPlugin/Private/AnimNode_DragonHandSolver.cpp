/* Copyright (C) Gamasome Interactive LLP, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Mansoor Pathiyanthra <codehawk64@gmail.com , mansoor@gamasome.com>, July 2018
*/


#include "AnimNode_DragonHandSolver.h"
#include "DragonIKPlugin.h"
#include "Animation/AnimInstanceProxy.h"
#include "DrawDebugHelpers.h"

#include "AnimationRuntime.h"
#include "AnimationCoreLibrary.h"
#include "Algo/Reverse.h"


DECLARE_CYCLE_STAT(TEXT("DragonHandSolver Eval"), STAT_DragonHandSolver_Eval, STATGROUP_Anim);



// Initialize the component pose as well as defining the owning skeleton
void FAnimNode_DragonHandSolver::Initialize_AnyThread(const FAnimationInitializeContext & Context)
{
	FAnimNode_Base::Initialize_AnyThread(Context);
	ComponentPose.Initialize(Context);
	owning_skel = Context.AnimInstanceProxy->GetSkelMeshComponent();
	//	dragon_bone_data.Start_Spine = FBoneReference(dragon_input_data.Start_Spine);
}



// Cache the bones . Thats it !!
void FAnimNode_DragonHandSolver::CacheBones_AnyThread(const FAnimationCacheBonesContext & Context)
{
	FAnimNode_Base::CacheBones_AnyThread(Context);
	ComponentPose.CacheBones(Context);
	InitializeBoneReferences(Context.AnimInstanceProxy->GetRequiredBones());
}


// Main update function . Do not perform any changed !!
void FAnimNode_DragonHandSolver::Update_AnyThread(const FAnimationUpdateContext & Context)
{
	ComponentPose.Update(Context);
	ActualAlpha = 0.f;


	if (IsLODEnabled(Context.AnimInstanceProxy))
	{

		GetEvaluateGraphExposedInputs().Execute(Context);
		//EvaluateGraphExposedInputs.Execute(Context);
		// Apply the skeletal control if it's valid



		ActualAlpha = AlphaScaleBias.ApplyTo(Alpha);

		if (FAnimWeight::IsRelevant(ActualAlpha) && IsValidToEvaluate(Context.AnimInstanceProxy->GetSkeleton(), Context.AnimInstanceProxy->GetRequiredBones()))
		{
			UpdateInternal(Context);



		}
	}
}






void FAnimNode_DragonHandSolver::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext & Output)
{


	// Apply the skeletal control if it's valid
	if (  (FVector(0,0,0)-Output.AnimInstanceProxy->GetActorTransform().GetScale3D()).Size()>0 &&FAnimWeight::IsRelevant(ActualAlpha) && IsValidToEvaluate(Output.AnimInstanceProxy->GetSkeleton(), Output.AnimInstanceProxy->GetRequiredBones()) && Output.ContainsNaN() == false)
	{


	//	EvaluateSkeletalControl_AnyThread(Output, BoneTransforms);






		//		GetAnimatedPoseInfo(Output.Pose);
		checkSlow(ContainsNaN(BoneTransforms));

		if (BoneTransforms.Num() > 0)
		{
		//	for(int i=0;i<BoneTransforms.Num();i++)
		//	GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, " Feet : " + owning_skel->GetBoneName(BoneTransforms[i].BoneIndex.GetInt()).ToString());


			const float BlendWeight = FMath::Clamp<float>(ActualAlpha, 0.f, 1.f);
			Output.Pose.LocalBlendCSBoneTransforms(BoneTransforms, BlendWeight);
		}
	}
	else
	{
	//	Output.ResetToRefPose();
		ComponentPose.EvaluateComponentSpace(Output);
	}

}






void FAnimNode_DragonHandSolver::ConditionalDebugDraw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp) const
{
	/*
#if WITH_EDITORONLY_DATA
	if (show_trace_in_game&&PreviewSkelMeshComp && PreviewSkelMeshComp->GetWorld())
	{
		for (int i = 0; i < TraceStartList.Num(); i++)
			DrawDebugLine(PreviewSkelMeshComp->GetWorld(), TraceStartList[i], TraceEndList[i], FColor::Red, false, 0.1f);

	}
#endif
*/
}

//Perform update operations inside this
void FAnimNode_DragonHandSolver::UpdateInternal(const FAnimationUpdateContext & Context)
{


}

//Nothing would be needed here
void FAnimNode_DragonHandSolver::EvaluateComponentSpaceInternal(FComponentSpacePoseContext & Context)
{
}

/*
void FAnimNode_DragonHandSolver::EvaluateBoneTransforms(USkeletalMeshComponent * SkelComp, FCSPose<FCompactPose>& MeshBases, TArray<FBoneTransform>& OutBoneTransforms)
{
}
*/

void FAnimNode_DragonHandSolver::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{



	SCOPE_CYCLE_COUNTER(STAT_DragonHandSolver_Eval);
	check(OutBoneTransforms.Num() == 0);





}






bool FAnimNode_DragonHandSolver::IsValidToEvaluate(const USkeleton * Skeleton, const FBoneContainer & RequiredBones)
{
	return true;

}


void FAnimNode_DragonHandSolver::Evaluate_AnyThread(FPoseContext & Output)
{
}


FAnimNode_DragonHandSolver::FAnimNode_DragonHandSolver()
{
	
}

void FAnimNode_DragonHandSolver::InitializeBoneReferences(FBoneContainer & RequiredBones)
{


}






FCollisionQueryParams FAnimNode_DragonHandSolver::getDefaultColliParams(FName name, AActor *me)
{

	const FName TraceTag(name);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, me);
	RV_TraceParams.bTraceComplex = true;
//	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	RV_TraceParams.TraceTag = TraceTag;

	//	me->GetWorld()->DebugDrawTraceTag = TraceTag;


	return RV_TraceParams;
}


void FAnimNode_DragonHandSolver::line_trace_func(USkeletalMeshComponent *skelmesh, FVector startpoint, FVector endpoint, FHitResult RV_Ragdoll_Hit, FName bone_text, FName trace_tag, FHitResult& Output, const FLinearColor& Fdebug_color)
{



	TArray<AActor*> ignoreActors;

	if (owning_skel->GetOwner())
	{
		ignoreActors.Add(owning_skel->GetOwner());

		UKismetSystemLibrary::LineTraceSingle(owning_skel->GetOwner(), startpoint, endpoint, Trace_Channel, true, ignoreActors, EDrawDebugTrace::None, RV_Ragdoll_Hit, true, Fdebug_color);

	}



	

	TraceStartList.Add(startpoint);
	TraceEndList.Add(endpoint);


	Output = RV_Ragdoll_Hit;

}



