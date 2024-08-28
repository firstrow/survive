EntityFinder = {}

function EntityFinder:by_id(id)
  return Entities[id]
end

function EntityFinder:by_tag(tag)
  local e = game.entity_by_tag(tag)
  if e == nil then
    return nil
  end
  return Entities[e.id]
end

return EntityFinder
