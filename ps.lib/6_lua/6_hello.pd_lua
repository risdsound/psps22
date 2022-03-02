-- This is an example I made to begin learning about pdlua
-- s3g 2016

-- class creation
local Sayhello = pd.Class:new():register("6_hello")

-- object initialization - on object creation
-- sel is the class name, atoms are creation arguments in a Lua table
-- in this case name = sayhello and atoms = Pd object arguments

function Sayhello:initialize(name, atoms)
  -- post to the Pd window
  pd.post("This is based on some of the pdlua examples.")
  pd.post("Hello, world!")
  -- 'initialize' has a 'self' variable
  -- default inlet/outlet counts are 0
  -- set number of inlets
  self.inlets = 4
  -- set number of outlets
  self.outlets = 4
  -- return allows object to fail to create, e.g. if creation arguments are bad
  return true
end

function Sayhello:postinitialize()
  -- not using this right now,
  -- but here is where one should register receivers or clocks
end

-- this will accept any input
function Sayhello:in_1(sel, atoms)
  -- pass inlet 1 to outlet 1
  -- does nothing to the input, just passes it
   self:outlet(1, sel, atoms)
end

-- this will accept any input
function Sayhello:in_2(sel, atoms)
  -- pass inlet 3 to outlet 3
  -- we'll simply take the input and create a bang
  self:outlet(2, "bang", {})
end

-- will only accept a float
function Sayhello:in_3_float(f)
  -- pass inlet 2 to outlet 2
  -- we'll add 10 to the input just to show we can
  self:outlet(3, "float", {f + 10})
end

-- this will accept any input
function Sayhello:in_4(sel, atoms)
  -- pass inlet 4 to outlet 4
  -- append some text to the incoming symbol
  listing = tostring(atoms[1]) -- convert atoms to string
  self:outlet(4, "list", {listing .. " appended with this statement"})
end

-- object finalization - on object deletion
-- can be used to clean up stuff if needed
function Sayhello:finalize()
  pd.post("Bye bye, world!")
end
