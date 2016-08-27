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

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QTextCharFormat keywordFormat;

    QVector<HighlightingRule> highlightingRules;

    std::set<QString> reservedKeywords;
    std::set<QString> functionKeywords;
};

#endif // RUBYSYNTAXHIGHLIGHTER_H
