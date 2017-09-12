-- pa2.lua
-- Bryan Burkhardt
-- 06 Feb 2017
-- Module pa2 for pa2_test.lua
-- CS331 - Assignment 2

local pa2 = {}

-- Function filterArray
-- filterArray accepts a function f and a table t.
-- filterArray returns an array containing values in given array for which
--		function f is true.
function pa2.filterArray(f, t)
	local arr = {}
	local idx = 1
	local i = 1

	while t[i]~=nil do
		if f(t[i]) then
			arr[idx] = t[i]
			idx = idx+1
		end
		i = i+1
	end
	return arr
	
end


-- Function concatMax
-- concatMax accepts a string s and integer n.
-- concatMax returns a string rv which is a concatenated string containing 
--		copies of the given string. The returned string will not be longer
--		than the given integer and will not contain an incomplete version
--		of the given string.
function pa2.concatMax(s, n)
	local rv = ""

	for i = 1, n/(s:len()) do
		rv = rv..s
	end
	return rv

end

-- Function collatz
-- collatz accepts an integer k
-- collatz performs the Collatz sequence on the given inerger. collatz 
--		utilizes coroutines to return each integer a required to complete
--		the sequence.
function pa2.collatz(k)
	local a=k

	while true do
		coroutine.yield(a)
		-- Done
		if a==1 then
			break
		-- Odd
		elseif (a%2)~=0 then
			a = (3*a)+1
		-- Even
		elseif (a%2)==0 then
			a = a/2
		end
	end

end

return pa2