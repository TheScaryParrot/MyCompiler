CompilerConstruction.pdf:
	rm -rf out
	latexmk -shell-escape -f -pdf -xelatex CompilerConstruction.tex -outdir=out
	detex CompilerConstruction.tex | wc -w
	
