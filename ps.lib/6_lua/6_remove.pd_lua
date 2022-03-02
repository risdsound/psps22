-- s3g 2016
-- an object for removing part of a string


local Remove = pd.Class:new():register("6_remove")

function Remove:initialize(name, atoms)
--  pd.post("6_remove")
  self.inlets = 2
  self.outlets = 1
  if type(atoms[1]) == "string" then self.rmstr = atoms[1]
  end
  return true
end

function Remove:in_2(sel, atoms)
  self.rmstr = tostring(atoms[1])
end

function Remove:in_1(sel, atoms)
  self.srcstr = tostring(atoms[1])
  self:outlet(1, "list", {string.gsub(self.srcstr, self.rmstr, "")})

end
