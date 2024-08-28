local M = {
  callbacks = {},
  current = 0,
  _prev_state = -1,
}

-- default keyboard handler
local default_callback = function(dt)
  local dirs = 0;
  local player = EntityFinder:by_tag("player")
  if player == nil then
    return
  end

  if game.input_key_hold(game.KEY_CROUCH) then
    player.components.sneaky:toggle()
  end

  if game.input_key(game.KEY_UP) then
    dirs = dirs | (1 << game.DIR_0_TOP)
  end
  if game.input_key(game.KEY_RIGHT) then
    dirs = dirs | (1 << game.DIR_2_RIGHT)
  end
  if game.input_key(game.KEY_DOWN) then
    dirs = dirs | (1 << game.DIR_4_BOTTOM)
  end
  if game.input_key(game.KEY_LEFT) then
    dirs = dirs | (1 << game.DIR_6_LEFT)
  end

  if dirs == 0 then
    player.entity.state = player.components.locomotor.idle_state
    return
  end

  local x, y = 0, 0

  if dirs == 1 then -- w
    x = -1
    y = -1
  end
  if dirs == 4 then -- d
    x = 1
    y = -1
  end
  if dirs == 16 then -- s
    x = 1
    y = 1
  end
  if dirs == 64 then -- a
    x = -1
    y = 1
  end
  if dirs == 65 then -- wa
    x = -1
    y = 0
  end
  if dirs == 5 then -- wd
    x = 0
    y = -1
  end
  if dirs == 20 then -- sd
    x = 1
    y = 0
  end
  if dirs == 80 then -- sa
    x = 0
    y = 1
  end

  local speed = 64.0
  if dirs == 4 or dirs == 64 then
    speed = 44.0
  end

  local dist = speed * player.components.locomotor.speed * dt

  local dest_x = player.entity.transform.world_pos.x + dist * x
  local dest_y = player.entity.transform.world_pos.y + dist * y

  player.entity.state = player.components.locomotor.moving_state
  player.components.locomotor:set_position(dest_x, dest_y)
end

function M.init()
  M.callbacks[M.current] = default_callback
end

function M.update(dt)
  M.callbacks[M.current](dt)
end

return M
