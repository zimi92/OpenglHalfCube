characters = ['[', ']', 'v', 'e', 'c', '(', ')', '2', '3', '4', '\\', 'n', '{' , '}', ';', ' ', '\n']
file = "model.txt"
with open(file) as f:
	content = f.readlines()
	for line in content:
		for it in characters:
			line = line.replace(it, "")	        
		print (line)