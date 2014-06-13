local a = {name="zhaowei", age=30, desc="哈哈"}
local enc = cjson.new()

local b1 = enc.encode(a)
print(b1)

local b2 = enc.decode(b1)
print(b2["name"], b2['age'], b2["desc"])

