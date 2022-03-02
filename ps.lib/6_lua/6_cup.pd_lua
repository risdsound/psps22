-- pd.post("This is a modification of the \"simplecounter\" pdlua example")

local TheCounter = pd.Class:new():register("6_cup")

function TheCounter:initialize(sel, atoms)
--  pd.post("6_cup")
  self.inlets = 3
  self.outlets = 1
  self.count = 0
  self.value = 1
  if type(atoms[1]) == "number" then self.count = atoms[1]
  end
  if type(atoms[2]) == "number" then self.value = atoms[2]
  end
  return true
end

function TheCounter:in_3_float(f)
  self.value = f
end


function TheCounter:in_2_float(f)
  self.count = f
end


function TheCounter:in_1_bang()
  self:outlet(1, "float", {self.count})
  self.count = self.count + self.value
end
