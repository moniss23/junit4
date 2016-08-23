#ifndef RUBYSYNTAXHIGHLIGHTER_H
#define RUBYSYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextEdit>
#include <set>
class RubySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:

    RubySyntaxHighlighter(QTextDocument *parent=0);

    QStringList keywords;
    QVector<QString> inputText;
    std::set<QString> reservedKeywords;
    std::set<QString> functionKeywords;
protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
private:
    struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };
    QTextCharFormat keywordFormat;

    HighlightingRule rule;
    QVector<HighlightingRule> highlightingRules;
};

#endif // RUBYSYNTAXHIGHLIGHTER_H
