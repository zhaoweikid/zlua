function echotable(t)  
   for k,v in pairs(t) do  
		  print("+++",k,v,"+++")  
   end  
end  

echotable(package.loaded)


local socket = require("socket")

sock = socket.bind('127.0.0.1', 10000, 128)



