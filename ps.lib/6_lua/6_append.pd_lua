-- s3g 2016
-- an object for combining two input atoms as strings
-- with space between items

local Appender = pd.Class:new():register("6_append")

function Appender:initialize(name, atoms)
--  pd.post("6_append")
  self.inlets = 2
  self.outlets = 1
  self.parttwo = "default"
  if type(atoms[1]) == "string" then self.parttwo = atoms[1]
  end
  return true
end

function Appender:in_2(sel, atoms)
  self.parttwo = tostring(atoms[1])
end

function Appender:in_1(sel, atoms)
  self.partone = tostring(atoms[1])
  self:outlet(1, "list", {self.partone .. " ".. self.parttwo})
end
