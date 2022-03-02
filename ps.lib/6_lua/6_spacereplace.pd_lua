-- s3g 2016
-- an object for substituting part of a string


local Substi = pd.Class:new():register("6_spacereplace")

function Substi:initialize(name, atoms)
--  pd.post("6_spacereplace")
  self.inlets = 2
  self.outlets = 1
  if type(atoms[1]) == "string" then self.spstr = atoms[1]
  end
  return true
end

function Substi:in_2(sel, atoms)
  self.spstr = tostring(atoms[1])
end

function Substi:in_1(sel, atoms)
  self.instr = tostring(atoms[1])
  self:outlet(1, "list", {string.gsub(self.instr, self.spstr, " ")})

end
