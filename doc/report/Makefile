# Generate all outputs for the project.
NAME=report

.PHONY: all clean help wc

# target: all - Default target. Cleans and compiles.
all : compile

# target: help - Display all targets.
help :
	egrep "#\starget:" [Mm]akefile  | cut -d " " -f3-

# target: clean - Deletes all generated files.
clean : 
	$(RM) $(NAME).aux
	$(RM) $(NAME).bbl
	$(RM) $(NAME).blg
	$(RM) $(NAME).dvi
	$(RM) $(NAME).log
	$(RM) $(NAME).out
	$(RM) $(NAME).pdf
	$(RM) $(NAME).ps
	$(RM) $(NAME).tpt
	$(RM) $(NAME).toc
	$(RM) q.log

# target: compile - Compiles and renders documents.
compile :
	pdflatex 	$(NAME).tex	# Generate PDF.
	bibtex		$(NAME).aux	# Go through all references.	
	pdflatex	$(NAME).tex	# Complete references.
	thumbpdf 	$(NAME).pdf	# Make thumbnails for the PDF.
	pdflatex	$(NAME).tex	# Incorporate the thumbnails.
