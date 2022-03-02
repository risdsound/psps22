-- Based on small stats library
-- credit = http://lua-users.org/wiki/SimpleStats

-- Table to hold statistical functions
stats={}

-- Get the sum of a table
function stats.sum( t )
  local sum = 0
  local count = 0

  for k,v in pairs(t) do
    if type(v) == 'number' then
      sum = sum + v
      count = count + 1
    end
  end
  return (sum)
end

-- s3g 2016
-- an object for finding the sum in a table

local Summer = pd.Class:new():register("6_sum")

function Summer:initialize(name, atoms)
--  pd.post("6_sum")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Summer:in_1(sel, atoms)
      self:outlet(1, "float", {stats.sum(atoms)})
end
