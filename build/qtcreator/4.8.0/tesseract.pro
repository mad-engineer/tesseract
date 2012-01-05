include(tesseract.pri)

SUBDIRS = base \
		  projects \
		  operations \
		  svgcanvas \
		  dynamic_help
		  
tesseract.depends = base

base.depends = 	projects \
				operations \
				svgcanvas \
				dynamic_help