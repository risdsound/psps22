-- s3g 2016
-- an object for getting substrings


local Substring = pd.Class:new():register("6_substring")

function Substring:initialize(name, atoms)
--  pd.post("6_substring")
  self.inlets = 3
  self.outlets = 1
  self.start = 1
  self.finish = 1
  if type(atoms[1]) == "number" then self.start = atoms[1]
  end
  if type(atoms[2]) == "number" then self.finish = atoms[2]
  end
  return true
end

function Substring:in_3_float(f)
  self.finish = f
end

function Substring:in_2_float(f)
  self.start = f
end

function Substring:in_1(sel, atoms)
  totalstring = tostring(atoms[1])
  self:outlet(1, "list", {string.sub(totalstring, self.start, self.finish)})
end
