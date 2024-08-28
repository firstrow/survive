local Sneaky = Class(function(self, inst)
  self.inst = inst
  self.sneaky_speed = 0.8
  self.is_active = false
  self._prev_speed = nil
end)

function Sneaky:toggle()
  if self._prev_speed == nil then
    self._prev_speed = self.inst.components.locomotor.speed
    self.inst.components.locomotor.speed = self.sneaky_speed
    self.inst.components.locomotor.idle_state = STATE_SNEAK_IDLE
    self.inst.components.locomotor.moving_state = STATE_SNEAK
  else
    self.inst.components.locomotor.speed = self._prev_speed
    self.inst.components.locomotor.idle_state = STATE_IDLE
    self.inst.components.locomotor.moving_state = STATE_RUN
    self._prev_speed = nil
  end
end

return Sneaky
