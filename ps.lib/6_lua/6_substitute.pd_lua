-- s3g 2016
-- an object for substituting part of a string


local Substitute = pd.Class:new():register("6_substitute")

function Substitute:initialize(name, atoms)
--  pd.post("6_substitute")
  self.inlets = 3
  self.outlets = 1
  if type(atoms[1]) == "string" then self.rstr = atoms[1]
  end
  if type(atoms[2]) == "string" then self.sstr = atoms[2]
  end
  return true
end

function Substitute:in_3(sel, atoms)
  self.sstr = tostring(atoms[1])
end

function Substitute:in_2(sel, atoms)
  self.rstr = tostring(atoms[1])
end

function Substitute:in_1(sel, atoms)
  self.istr = tostring(atoms[1])
  self:outlet(1, "list", {string.gsub(self.istr, self.rstr, self.sstr)})

end
