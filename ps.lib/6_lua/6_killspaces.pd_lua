-- s3g 2016
-- an object for removing spaces between characters in a string


local Killspaces = pd.Class:new():register("6_killspaces")

function Killspaces:initialize(name, atoms)
--  pd.post("6_killspaces")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Killspaces:in_1(sel, atoms)
  self.astr = tostring(atoms[1])
  self:outlet(1, "list", {string.gsub(self.astr, "%s+", "")})
end
