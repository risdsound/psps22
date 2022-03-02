-- s3g 2016
-- an object for concatenating two input atoms as strings

local Concater = pd.Class:new():register("6_concat")

function Concater:initialize(name, atoms)
--  pd.post("6_concat")
  self.inlets = 2
  self.outlets = 1
  self.parttwo = "default"
  if type(atoms[1]) == "string" then self.parttwo = atoms[1]
  end
  return true
end

function Concater:in_2(sel, atoms)
  self.parttwo = tostring(atoms[1])
end

function Concater:in_1(sel, atoms)
  self.partone = tostring(atoms[1])
  self:outlet(1, "list", {self.partone .. self.parttwo})
end
