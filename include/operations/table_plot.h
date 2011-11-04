#pragma once
#ifndef TESSERACT_OPERATIONS_TABLE_PLOT_H
#define TESSERACT_OPERATIONS_TABLE_PLOT_H

#include <QString>

class ComplexNumberTableModel;

class TablePlot: public QDialog
{
	Q_OBJECT
	Type type;

	QRadioButton *use_rows;
	QRadioButton *use_cols;

	QLineEdit *x_lineedit, *y_lineedit, *x_error_lineedit, *y_error_lineedit;
	QLineEdit *title_lineedit;

	QComboBox *style_combo, *color_combo, *point_combo;

	QTableView *table;
	ComplexNumberTableModel *model;

	public:

	enum Type 
	{
		PLOT, 
		SEMILOGY, 
		SEMILOGX, 
		LOGLOG, 
		POLAR, 
		BAR
	};

	TablePlot(QWidget *parent, QTableView *table, ComplexNumberTableModel *model, Type type = PLOT);

	QString command();
};

#endif 
