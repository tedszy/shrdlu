MARKDOWN = pandoc --from markdown_github --to html 

doc: README.md
	$(MARKDOWN) $< --output README.html
