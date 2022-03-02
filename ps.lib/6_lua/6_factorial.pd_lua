-- s3g 2016

local Factorial = pd.Class:new():register("6_factorial")

function Factorial:initialize(name, atoms)
--  pd.post("6_factorial")
  self.inlets = 1
  self.outlets = 1
  return true
end

function fact (n)
  if n == 0 then
    return 1
  else
    return n * fact(n-1)
  end
end

function Factorial:in_1_float(f)
    self.pos = math.abs(f)
    self.dwn = math.floor(self.pos)
    self:outlet(1, "float", {fact(self.dwn)})
end
