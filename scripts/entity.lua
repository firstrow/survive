LoadedComponents = {}

local Entity = Class(function (self, ent_props)
  local id = game.entity_create()
  local ent = game.entity_get(id)

  for k, v in pairs(ent_props) do
    ent[k] = v
  end

	self.entity = ent
  self.components = {}

  Entities[id] = self
end)

function Entity:add_animation(state, anim)
  game.entity_anim_add(self.entity, state, anim)
end

function Entity:add_component(name, component_props)
  if LoadedComponents[name] == nil then
    LoadedComponents[name] = require('components/' .. name)
  end

  local cmp = LoadedComponents[name](self)
  for k, v in pairs(component_props) do
    cmp[k] = v
  end

  self.components[name] = cmp
end

return Entity
