-- s3g 2016
-- an object for getting the length of strings


local Length = pd.Class:new():register("6_length")

function Length:initialize(name, atoms)
-- pd.post("6_length")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Length:in_1(sel, atoms)
  stringlength = tostring(atoms[1])
  self:outlet(1, "float", {string.len(stringlength)})
end
