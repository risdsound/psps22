-- s3g 2016
-- an object for concatenating repetitions of strings


local Rep = pd.Class:new():register("6_repeat")

function Rep:initialize(name, atoms)
--  pd.post("6_repeat")
  self.inlets = 2
  self.outlets = 1
  self.value = 2
  if type(atoms[1]) == "number" then self.value = atoms[1]
  end
  return true
end

function Rep:in_2_float(f)
  self.value = f
end

function Rep:in_1(sel, atoms)
  self.instring = tostring(atoms[1])
  self:outlet(1, "list", {string.rep(self.instring, self.value)})
end
