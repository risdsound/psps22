-- s3g 2016
-- an object for matching of patterns in a string


local Match = pd.Class:new():register("6_match")

function Match:initialize(name, atoms)
--  pd.post("6_match")
  self.inlets = 2
  self.outlets = 1
  if type(atoms[1]) == "string" then self.pstr = atoms[1]
  end
  return true
end

function Match:in_2(sel, atoms)
  self.pstr = tostring(atoms[1])
end


function Match:in_1(sel, atoms)
  self.mstr = tostring(atoms[1])
  for w in string.gmatch(self.mstr, self.pstr) do
    self:outlet(1, "list", {w})
  end
end
