local a = {name="zhaowei", age=30, desc="哈哈"}

local b1 = cmsgpack.pack(a)
print(b1)

local b2 = cmsgpack.unpack(b1)
print(b2["name"], b2['age'], b2["desc"])

