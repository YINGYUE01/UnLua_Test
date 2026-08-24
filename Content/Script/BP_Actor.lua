local BP_Actor = UnLua.Class()

function BP_Actor:ReceiveBeginPlay()
 
print("========== BeginPlay ==========")

end

function BP_Actor:ReceiveTick(DeltaSeconds)
    self:AddScore()
    --print(self.Score)
    self:K2_AddActorWorldOffset(
    UE.FVector(100 * DeltaSeconds, 0, 0),
    true,
    nil,
    true
)
end

return BP_Actor