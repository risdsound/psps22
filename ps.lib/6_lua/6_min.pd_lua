-- s3g 2016

local Sortmin = pd.Class:new():register("6_min")

function Sortmin:initialize(name, atoms)
--  pd.post("6_min")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Sortmin:in_1(sel, atoms)
      table.sort(atoms)
      self:outlet(1, "list", {atoms[1]})
end
