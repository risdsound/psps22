-- s3g 2016
-- an object for reversing strings


local Reverse = pd.Class:new():register("6_reverse")

function Reverse:initialize(name, atoms)
--  pd.post("6_reverse")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Reverse:in_1(sel, atoms)
  self.listing = tostring(atoms[1])
  self:outlet(1, "list", {string.reverse(self.listing)})
end
