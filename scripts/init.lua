-- print("lua search paths:", package.path)
local kb_handler = require('keyboard_handler')
require('utils')
require('class')
require('entity_finder')

STATE_DELETED = -1
STATE_UNDEFINED = 0
STATE_RUN = 1
STATE_IDLE = 2
STATE_SNEAK = 3
STATE_SNEAK_IDLE = 4

Entity = require('entity')
Entities = Entities or {}

if Initialized == nil then
  kb_handler.init()

  local player = Entity({
    tag = "player",
    state = STATE_IDLE,
  });

  player:add_component('locomotor', {
    speed = 1.5,
    idle_state = STATE_IDLE,
    moving_state = STATE_RUN,
  })
  player:add_component('sneaky', {
    sneaky_speed = 0.8,
  })

  player:add_animation(STATE_RUN, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/run.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 19,
    loop = true,
    time_per_frame = 30,
    offset_x = 32,
    offset_y = 46,
  })))

  player:add_animation(STATE_IDLE, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/idle.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 20,
    loop = true,
    time_per_frame = 40,
    offset_x = 32,
    offset_y = 46,
  })))

  player:add_animation(STATE_SNEAK, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/sneak.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 20,
    loop = true,
    time_per_frame = 65,
    offset_x = 32,
    offset_y = 46,
  })))

  player:add_animation(STATE_SNEAK_IDLE, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/sneak.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 21,
    loop = false,
    time_per_frame = 0,
    offset_x = 32,
    offset_y = 46,
    current_frame = 11,
  })))

  player.entity.transform.world_pos.x = 500;
  player.entity.transform.world_pos.y = 500;



  local second_player = Entity({
    state = STATE_SNEAK_IDLE,
  });

  second_player:add_component('locomotor', {
    speed = 1.5,
    idle_state = STATE_SNEAK_IDLE,
    moving_state = STATE_RUN,
  })
  -- second_player:add_component('sneaky', {
  --   sneaky_speed = 0.8,
  -- })

  second_player:add_animation(STATE_RUN, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/run.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 19,
    loop = true,
    time_per_frame = 30,
    offset_x = 32,
    offset_y = 46,
  })))

  second_player:add_animation(STATE_IDLE, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/idle.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 20,
    loop = true,
    time_per_frame = 40,
    offset_x = 32,
    offset_y = 46,
  })))

  second_player:add_animation(STATE_SNEAK, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/sneak.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 20,
    loop = true,
    time_per_frame = 65,
    offset_x = 32,
    offset_y = 46,
  })))

  second_player:add_animation(STATE_SNEAK_IDLE, game.gfx_animation_create(TypeInit(game.animation_t, {
    texture_id = game.gfx_texture_load(TypeInit(game.texture_t, {
      filename = "character/sneak.png",
      cell_w = 64,
      cell_h = 64,
    })),
    max_frames = 21,
    loop = false,
    time_per_frame = 0,
    offset_x = 32,
    offset_y = 46,
    current_frame = 11,
  })))

  second_player.entity.transform.world_pos.x = 300;
  second_player.entity.transform.world_pos.y = 500;

  Initialized = true
end

function Reload(module)
  module = module:gsub(".lua", "")
  print("lua reloading:", module)
  package.loaded[module] = nil
  return require(module)
end

function Update(dt)
  kb_handler.update(dt)
end
