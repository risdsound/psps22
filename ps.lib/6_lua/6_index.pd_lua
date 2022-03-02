-- s3g 2016
-- an object for adding an index for each item in a list

local Indx = pd.Class:new():register("6_index")

function Indx:initialize(name, atoms)
--  pd.post("6_index")
  self.inlets = 1
  self.outlets = 1
  return true
end

function Indx:in_1(sel, atoms)
      for i, v in ipairs(atoms) do
        self:outlet(1, "list", {i, v})
      end
end
