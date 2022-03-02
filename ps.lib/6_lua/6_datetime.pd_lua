-- s3g 2016
-- get date from OS via Lua

local Osdate = pd.Class:new():register("6_datetime")

function Osdate:initialize(name, atoms)
--  pd.post("6_datetime")
  self.inlets = 1
  self.outlets = 7
  return true
end

function Osdate:in_1(sel, atoms)
  self.wkdy = tonumber(os.date("%w"))
  self.date = tonumber(os.date("%d"))
  self.month = tonumber(os.date("%m"))
  self.year = tonumber(os.date("%Y"))
  self.hour = tonumber(os.date("%H"))
  self.minute = tonumber(os.date("%M"))
  self.second = tonumber(os.date("%S"))
  self:outlet(1, "float", {self.wkdy})-- day of week
  self:outlet(2, "float", {self.date})-- date
  self:outlet(3, "float", {self.month}) -- month
  self:outlet(4, "float", {self.year}) -- year
  self:outlet(5, "float", {self.hour}) -- hour
  self:outlet(6, "float", {self.minute}) -- minute
  self:outlet(7, "float", {self.second}) -- second

end
