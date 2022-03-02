-- s3g 2016
-- an object for parsing comma separated values and outputting with index

local Csvparse = pd.Class:new():register("6_csv")

function Csvparse:initialize(name, atoms)
--  pd.post("6_csv")
  self.inlets = 1
  self.outlets = 1
  return true
end

-- fromCSV function from http://www.lua.org/pil/20.4.html
function fromCSV (s)
      s = s .. ","       -- ending delimiter
      local t = {}        -- table to collect fields
      local fieldstart = 1
      repeat
        -- next field is quoted? (start with `"'?)
        if string.find(s, '^"', fieldstart) then
          local a, c
          local i  = fieldstart
          repeat
            -- find closing quote
            a, i, c = string.find(s, '"("?)', i+1)
          until c ~= '"'    -- quote not followed by quote?
          if not i then error('unmatched "') end
          local f = string.sub(s, fieldstart+1, i-1)
          table.insert(t, (string.gsub(f, '""', '"')))
          fieldstart = string.find(s, ",", i) + 1
        else                -- unquoted; find next pipe
          local nexti = string.find(s, ",", fieldstart)
          table.insert(t, string.sub(s, fieldstart, nexti-1))
          fieldstart = nexti + 1
        end
      until fieldstart > string.len(s)
      return t
end


function Csvparse:in_1(sel, atoms)
      line = tostring(atoms[1])
      t = fromCSV(line)
      for i, s in ipairs(t) do
      self:outlet(1, "list", {i, s})
      end
end
