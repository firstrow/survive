
-- better syntax for C sturcts initializing
TypeInit = function(type_cb, vals)
  local t = type_cb()
  for k, v in pairs(vals) do
    t[k] = v
  end
  return t
end

