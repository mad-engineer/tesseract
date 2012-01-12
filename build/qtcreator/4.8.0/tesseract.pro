include(tesseract.pri)

SUBDIRS = base \
		  config \
		  projects \
		  operations \
		  svgcanvas \
		  dynamic_help
		  
tesseract.depends = base

base.depends = 	projects \
				config \
				operations \
				svgcanvas \
				dynamic_help