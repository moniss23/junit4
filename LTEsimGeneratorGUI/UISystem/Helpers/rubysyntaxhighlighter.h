#ifndef RUBYSYNTAXHIGHLIGHTER_H
#define RUBYSYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextEdit>
#include <set>

/**
 * @brief The RubySyntaxHighlighter class is responsible for highlighting Ruby scripts
 */
class RubySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:

    RubySyntaxHighlighter(QTextDocument *parent=0);

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
protected:
    /**
     * @brief highlightBlock applies highlighting rules to the specified block of text
     * @param text
     */
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule                         ///< Highlighting rule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QTextCharFormat keywordFormat;                  ///< Format of keywords

    QVector<HighlightingRule> highlightingRules;    ///< Vector of rules

    std::set<QString> reservedKeywords;             ///< Set of keywords coloured as reserved
    std::set<QString> functionKeywords;             ///< Set of keywords colored as function keywords
};

#endif // RUBYSYNTAXHIGHLIGHTER_H
