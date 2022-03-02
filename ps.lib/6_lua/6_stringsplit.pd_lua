-- from: http://lua-users.org/wiki/SplitJoin
-- (JoanOrdinas)

function string:split(sSeparator, nMax, bRegexp)
	assert(sSeparator ~= '')
	assert(nMax == nil or nMax >= 1)

	local aRecord = {}

	if self:len() > 0 then
		local bPlain = not bRegexp
		nMax = nMax or -1

		local nField=1 nStart=1
		local nFirst,nLast = self:find(sSeparator, nStart, bPlain)
		while nFirst and nMax ~= 0 do
			aRecord[nField] = self:sub(nStart, nFirst-1)
			nField = nField+1
			nStart = nLast+1
			nFirst,nLast = self:find(sSeparator, nStart, bPlain)
			nMax = nMax-1
		end
		aRecord[nField] = self:sub(nStart)
	end

	return aRecord
end


-- s3g 2016
-- an object for splitting strings based on a delimiter

local Stringersplit = pd.Class:new():register("6_stringsplit")

function Stringersplit:initialize(name, atoms)
  self.inlets = 2
  self.outlets = 1
  if type(atoms[1]) == "string" then self.delim = atoms[1]
  end
  return true
end

function Stringersplit:in_2(sel, atoms)
  self.delim = tostring(atoms[1])
end

function Stringersplit:in_1(sel, atoms)
  self.str = tostring(atoms[1])
  for k,v in next, string.split(self.str, self.delim) do
    self:outlet(1, "list", {v})
  end
end
