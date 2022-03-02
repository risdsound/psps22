-- s3g 2016
-- an object for finding base-10 logarithm of input number

local Logger = pd.Class:new():register("6_log10")

function Logger:initialize(name, atoms)
--  pd.post("6_log10")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Logger:in_1_float(f)
  self.pos = math.abs(f)
  self.value = math.log10(self.pos)
  self:outlet(1, "float", {self.value})
end
