-- s3g 2016
-- an object for adding spaces between characters in a string

local Addspaces = pd.Class:new():register("6_addspaces")

function Addspaces:initialize(name, atoms)
--  pd.post("6_addspaces")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Addspaces:in_1(sel, atoms)
  self.astr = tostring(atoms[1])
  self:outlet(1, "list", {string.gsub(self.astr, ".", "%0 ")})
end
