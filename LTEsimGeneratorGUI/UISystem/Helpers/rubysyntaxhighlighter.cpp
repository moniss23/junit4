#include "rubysyntaxhighlighter.h"

RubySyntaxHighlighter::RubySyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{

    HighlightingRule rule;


    // RESERVED KEYWORDS
    reservedKeywords={"BEGIN","class","ensure","nil","self","when","END",
          "def","not","super","while","alias","define",
          "for","or","then","yield","and","do","if","redo",
          "begin","else","in","rescu","undef","break","elsif",
          "module","retry","unless","case","end","next",
          "return","until"};
    keywordFormat.setForeground(Qt::blue);
    foreach (const QString &pattern, reservedKeywords) {
        rule.pattern = QRegExp(pattern+"\\s");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // FUNCTION KEYWORDS
    functionKeywords={"abort","Array","at_exit","autoload","binding","block_given?"
          ,"callcc","caller","catch","chomp","chomp!","chop",
         "eval","exec","exit","fail","Float","fork","format",
         "gets","global_variables","gsub","Integer","lambda",
         "load","local_variables","loop","open","p","print",
         "printf","proc","putc","puts","raise","rand",
         "readline","readlines","require","scan","select",
         "set_trace_func","split","sprintf","srand","String",
         "sub","test","throw","trap","untrace_var"};
    keywordFormat.setForeground(Qt::darkRed);
    foreach (const QString &pattern, functionKeywords) {
        rule.pattern = QRegExp(pattern+"\\s");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // INDEXES
    keywordFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("\\[:\\w*\\]");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // NUMBERS
    keywordFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\\d+");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // OPERATION ON NUMBERS
    keywordFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("= [0-9]+[+-/*]+[0-9]+");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // TRUE / FALSE
    keywordFormat.setForeground(Qt::darkYellow);
    rule.pattern = QRegExp("\\b(true|false)\\b");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // END
    keywordFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("end$");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // ASSIGN
    keywordFormat.setForeground(Qt::darkCyan);
    rule.pattern = QRegExp("=>");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // QUOTE
    keywordFormat.setForeground(Qt::darkMagenta);
    //rule.pattern = QRegExp("\".*\"");
    rule.pattern = QRegExp("\"(\\\\\"|[^\"])+\"");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // COMMENT
    keywordFormat.setForeground(QColor(160,82,45, 255));
    rule.pattern = QRegExp("#.*$");
    rule.format = keywordFormat;
    highlightingRules.append(rule);

}
void RubySyntaxHighlighter::highlightBlock(const QString &text){
    foreach (const HighlightingRule &rule, highlightingRules) {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(text);
            while (index >= 0 and index<=text.length() ) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = expression.indexIn(text, index + length);
            }
        }
}
