-- s3g 2016
-- an object for making uppercase characters lowercase


local Lower = pd.Class:new():register("6_lower")

function Lower:initialize(name, atoms)
--  pd.post("6_lower")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Lower:in_1(sel, atoms)
  self.uppercase = tostring(atoms[1])
  self:outlet(1, "list", {string.lower(self.uppercase)})
end
