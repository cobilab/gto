import os

def linkBuilder(file, home=False):
	'''
	It reads from a file a list of tool by section.
	The main reason is to keep the same order of the tools (readme, manual, home page and dropdowns)
	### 1. FASTQ tools
	#format: 1.1 gto_fastq_to_fasta
	'''
	with open(file) as f:
	    content = f.readlines()
	# you may also want to remove whitespace characters like `\n` at the end of each line
	content = [x.strip() for x in content] 
	print("don't forget to manually edit the decompressor url")
	for each in content:
		if("###" in each):
			section = getDestination(each)
		else:
			line = each.split()
			#<a class="dropdown-item" href="#">Action</a>
			if home:
				print('<a href="/gto/' + section +'/' + line[1] +'.html">' + each + '</a><br>')
			else:
				print('<a class="dropdown-item" href="/gto/' + section +'/' + line[1] +'.html">Program ' + line[1] + '</a>')

templateHead="""
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>GTO - The Genomic Toolkit</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1"> 
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">

    <!-- jQuery library -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>

    <!-- Popper JS -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"></script>

    <!-- Latest compiled JavaScript -->
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script> 
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script>
    $(document).ready(function(){
       $('#navbar').load("/gto/navbar.html");
       $('#footer').load("/gto/footer.html");
    });
    </script>
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.6.3/css/all.css" integrity="sha384-UHRtZLI+pbxtHCWp1t77Bi1L4ZtiqrqD80Kn4Z8NTSRyMA2Fd33n5dQ8lWUE00s/" crossorigin="anonymous">
    <link rel="stylesheet" href="/gto/style.css">
    <link rel="stylesheet" href="/gto/icons/styles.css">
  </head>
  <body>

    <div id="navbar"></div>
"""      
templateFooter="""
    <div id="footer"></div>
  </body>
</html>
"""

def getDestination(path):
	if("FASTA" in path):
		return "fasta_tools"
	if("FASTQ" in path):
		return "fastq_tools"
	if("General" in path):
		return "general_tools"
	if("Amino" in path):
		return "amino_tools"
	if("Genomic" in path):
		return "genomic_tools"
	return ""

def getHTML(s):
	if "FastqUnpack" in s:
		print "Perform manual changes in gto_fastq_unpack.html"
	if "XS" in s:
		print "Perform manual changes in gto_fastq_xs.html"
	#This tools do not have the local in the tex file name
	if "NewLineForNewValue" in s:
		s = s.replace("NewLineForNewValue", "NewLineOnNewX")
	if "FastqMinimumQualityScoreForward" in s:
		s = s.replace("FastqMinimumQualityScoreForward", "FastqMinimumLocalQualityScoreForward")
	if "FastqMinimumQualityScoreReverse" in s:
		s = s.replace("FastqMinimumQualityScoreReverse", "FastqMinimumLocalQualityScoreReverse")

	if "DNA" in s: #When _ not should be put before all upper letters
		s = s.replace("DNA", "Dna")
	if "MFasta" in s: #When _ not should be put before all upper letters
		s = s.replace("MFasta", "Mfasta")
	temp = "gto"+("".join(["_" + ch.lower() if ch.isupper() else ch for ch in s]))
	return temp.split(".")[0] + ".html"

def readTex(source):
	begin = """<div class="container-fluid"><br/><br/><br/>
	"""    
	end = """</div><br/><br/><br/><br/>"""
	content=""
	startListing = False
	startFigure = False

	file = open(source, "r") 
	for line in file: 
		line = line.strip().replace("\\\\", "").replace("\char`_", "_")
		if(startListing):
			if("end{lst" in line):
				startListing = False
				content += "</p></code></div></div><br>"
				continue
			content +=  line + "<br>"
			continue

		if(startFigure):
			if("includegraphics" in line):#Not good but works too
				line = "/sections/images" + line.split("images")[1][:-1]
				content += "<img src='" + line + "'>"

			if("end{figure}" in line):
				startFigure = False
			continue

		if("\section" in line):
			value = line.split("{")[1][:-1]
			programName = "gto" + value.split("gto")[1]
			value = "<h1>" + value + "</h1>"
			content += value + "\n"
			continue

		if("texttt{" in line):
			replace="\\texttt{"+programName+"}"
			replacement = "<strong>" + programName + "</strong>"
			line = line.replace(replace, replacement)

		if("\subsection" in line):
			value = line.split("{")[1][:-1]
			value = "<h3>" + value + "</h3>"
			content += value + "\n"
			continue

		if("begin{lst" in line):
			startListing = True
			#content += "<code><p>"
			content += """
			<div class="card">
				<div class="card-body">
					<code>
			  			<p>"""
			continue
			
		if("begin{figure" in line):
			startFigure = True
			continue

		if("ref{fig" in line): #NOT GOOD but works
			line = line.replace("~\\ref{fig", "{")
			line = line.split("{")[0]+line.split("{")[1].split("}")[1]

		value = "<p>" + line + "</p>"
		content += value + "\n"


	return begin + content + end

def manualExtraction():
	'''
	Instructions:
	- Remove Introduction.text and only mantain the sections dirs inside od "sections"

	'''
	allTex = []
	for path, subdirs, files in os.walk("sections"):
	    for name in files:
	    	if(name.find('_') == -1): #e para considerar
	    		destination = getDestination(path)
	    		programName = getHTML(name)
	    		allTex.append((os.path.join(path, name),destination,programName))

	for source, destination, name in allTex:
		if not os.path.exists(destination):
			os.makedirs(destination)
		htmlFile = open(destination + "/" + name, "w")
		htmlFile.write(templateHead) 
		htmlFile.write(readTex(source))
		htmlFile.write(templateFooter) 


import argparse

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("-m", "--manual", help="Extract the manual pages ande creates the html", action="store_true")
	parser.add_argument("-lb", "--linkbar", help="Prints the links for the navbar", action="store_true")
	parser.add_argument("-lh", "--linkhome", help="Prints the links for the home page", action="store_true")
	parser.add_argument("-f", "--file",  type=str, help="File with the tools")
	parser.add_argument("-t", "--type",  type=str, help="Tool type (ex: fastq)")
	args = parser.parse_args()

	if args.manual:
		print "Build html pages"
		manualExtraction()
	elif args.linkbar:
		linkBuilder("tools")#args.file, args.type)
	elif args.linkhome:
		linkBuilder("tools", True)


if __name__ == "__main__":
   main()