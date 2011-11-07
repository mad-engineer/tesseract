include(tesseract.pri)

SUBDIRS = base \
		  projects \
		  operations \
		  svgcanvas \
		  dynamic_help
		  
tesseract.depends = projects \
					operations \
					svgcanvas \
					dynamic_help
