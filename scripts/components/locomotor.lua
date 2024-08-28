local Locomotor = Class(function(self, inst)
    self.inst = inst
    self.speed = 1
    self.idle_state = -1
    self.moving_state = -1
end)

function Locomotor:set_position(x, y)
    local direction = game.entity_calc_general_direction(
        self.inst.entity.transform.world_pos.x,
        self.inst.entity.transform.world_pos.y,
        x,
        y
    )
    self.inst.entity.transform.direction = direction

    if game.map_check_world_bounds(x, y) == true then
        self.inst.entity.transform.world_pos.x = x
        self.inst.entity.transform.world_pos.y = y
    end
end

return Locomotor
