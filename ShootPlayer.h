#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ShootPlayer.generated.h"

UCLASS()
class SHOOTERGAME_API UShootPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UShootPlayer();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory) override;
};
