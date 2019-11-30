/* Copyright (C) Gamasome Interactive LLP, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Mansoor Pathiyanthra <codehawk64@gmail.com , mansoor@gamasome.com>, July 2018
*/

#pragma once



#include "DragonIK_Library.h"
#include "CoreMinimal.h"

#include "DragonIKPlugin.h"

#include "Kismet/KismetMathLibrary.h"

#include "CollisionQueryParams.h"

#include "Animation/InputScaleBias.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_DragonHandSolver.generated.h"
/**
 * 
 */


class USkeletalMeshComponent;



/*
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EIK_Type_Plugin : uint8
{
	ENUM_Two_Bone_Ik 	UMETA(DisplayName = "Two Bone IK"),
	ENUM_Single_Bone_Ik 	UMETA(DisplayName = "Single Bone IK")

};
*/


USTRUCT(BlueprintInternalUseOnly)
struct DRAGONIKPLUGIN_API FAnimNode_DragonHandSolver : public FAnimNode_Base
{
	//	GENERATED_USTRUCT_BODY()
	GENERATED_BODY()



		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputData, meta = (PinShownByDefault))
		FDragonData_MultiInput dragon_input_data;

	FDragonData_BoneStruct dragon_bone_data;

public:


	FAnimNode_DragonHandSolver();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
		FComponentSpacePoseLink ComponentPose;

	// Current strength of the skeletal control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))
		mutable float Alpha = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		FInputScaleBias AlphaScaleBias;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
			TEnumAsByte<ETraceTypeQuery> Trace_Channel = ETraceTypeQuery::TraceTypeQuery1;




		TArray<FVector> TraceStartList = TArray<FVector>();
		TArray<FVector> TraceEndList = TArray<FVector>();



		USkeletalMeshComponent *owning_skel;
		TArray<FBoneTransform> BoneTransforms;


		virtual void ConditionalDebugDraw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp) const;


		FCollisionQueryParams getDefaultColliParams(FName name, AActor *me);

		void line_trace_func(USkeletalMeshComponent *skelmesh, FVector startpoint, FVector endpoint, FHitResult RV_Ragdoll_Hit, FName bone_text, FName trace_tag, FHitResult& Output, const FLinearColor& Fdebug_color = FLinearColor::White);


		UPROPERTY(Transient)
			float ActualAlpha = 0;

	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)  override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;


	virtual void Evaluate_AnyThread(FPoseContext& Output);


protected:
	// Interface for derived skeletal controls to implement
	// use this function to update for skeletal control base
	virtual void UpdateInternal(const FAnimationUpdateContext& Context);
	// use this function to evaluate for skeletal control base
	virtual void EvaluateComponentSpaceInternal(FComponentSpacePoseContext& Context);
	// Evaluate the new component-space transforms for the affected bones.
	//	virtual void EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, FCSPose<FCompactPose>& MeshBases, TArray<FBoneTransform>& OutBoneTransforms);

	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms);


	void LineTraceControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms);


	// return true if it is valid to Evaluate
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones);
	// initialize any bone references you have
	virtual void InitializeBoneReferences(FBoneContainer& RequiredBones);

};

