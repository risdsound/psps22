-- s3g 2016
-- an object for finding the maximum value in a list

local Max = pd.Class:new():register("6_max")

function Max:initialize(name, atoms)
--  pd.post("6_max")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Max:in_1(sel, atoms)
      table.sort(atoms)
      self:outlet(1, "list", {atoms[#atoms]})
end
