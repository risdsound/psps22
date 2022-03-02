-- s3g 2016
-- an object for making lowercase characters uppercase


local Upper = pd.Class:new():register("6_upper")

function Upper:initialize(name, atoms)
--  pd.post("6_upper")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Upper:in_1(sel, atoms)
  self.lowercase = tostring(atoms[1])
  self:outlet(1, "list", {string.upper(self.lowercase)})
end
