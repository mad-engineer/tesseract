/* Copyright (C) 2010 P.L. Lucas
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#pragma once
#ifndef TESSERACT_BASE_SYNTAX_HPP
#define TESSERACT_BASE_SYNTAX_HPP

#include <memory>
using std::tr1::shared_ptr;

#include <vector>
using std::vector;

#include <QVector>
#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextBlockUserData>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

struct BlockData:public QTextBlockUserData
{
	struct Bracket
	{
		int type;	//Type of bracket
		int pos;	//Position of bracket
		int length;	//Number of chars of bracket
		bool startBracketOk;	//Is it a start or end bracket?
	};
	
	vector<Bracket> brackets;
};

class Syntax:public QSyntaxHighlighter
{
	Q_OBJECT
	
	QString xmlSyntaxFileName;
	
	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
		int ruleOrder;
		int lastFound;
	};
	
	vector<HighlightingRule> highlightingRules;
	
	struct HighlightingBlockRule
	{
		QRegExp startPattern, endPattern;
		QTextCharFormat format;
		int ruleOrder;
	};
	
	vector<HighlightingBlockRule> highlightingBlockRules;
	vector<HighlightingBlockRule> highlightingBracketsRules;
	
	struct Rule1st
	{
		int rule;
		int startIndex;
		int length;
		int ruleOrder;
	};
	
	/**1st rule to apply from startIndex.
	 */
	shared_ptr<Rule1st> highlight1stRule(const QString & text, int startIndex );
	
	/**1st block rule to apply from startIndex.
	 */
	shared_ptr<Rule1st> highlight1stBlockRule(const QString & text, int startIndex );
	
	/** Set format using rule.
	 */
	int ruleSetFormat( const shared_ptr<Rule1st> &rule );
	
	/** Set format using block rule.
	 */
	int blockRuleSetFormat(const QString & text, const shared_ptr<Rule1st> &rule1st );
	
	/** Finds brackets and put them in BlockData.
	 */
	void findBrackets(const QString & text, int start, int end, BlockData *blockData );
	
	protected:
		
		void highlightBlock ( const QString & text );

	public:
	
		Syntax(QObject * parent = 0);
		bool load( const QString &file );
		
		/**Formats pair of brackets
		 */
		void setFormatPairBrackets( QPlainTextEdit *textEdit );
	

};
#endif
