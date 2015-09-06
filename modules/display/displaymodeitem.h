#ifndef DISPLAYMODEITEM_H
#define DISPLAYMODEITEM_H

#include <QLabel>

class DisplayModeItem : public QLabel
{
    Q_OBJECT

    Q_PROPERTY(QString iconName READ iconName WRITE setIconName)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(bool hover READ hover NOTIFY hoverChanged)
    Q_PROPERTY(bool clickCheck READ clickCheck WRITE setClickCheck)

public:
    explicit DisplayModeItem(bool showSeparator = true, bool showTitle = true, QWidget *parent = 0);
    ~DisplayModeItem();

    QString iconName() const;
    QString title() const;
    QString text() const;
    bool checked() const;
    bool hover() const;
    bool clickCheck() const;

public slots:
    void setIconName(QString iconName);
    void setTitle(QString title);
    void setText(QString text);
    void setChecked(bool checked);
    void setClickCheck(bool clickCheck);

signals:
    void hoverChanged(bool hover);
    void checkedChanged(bool checked);
    void clicked();

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void setHover(bool arg);
    void updateIcon();

private:
    static DisplayModeItem *activeItem;

    QString m_iconName;
    QString m_iconPath;
    QLabel *m_title;
    QLabel *m_text;
    bool m_checked;
    bool m_hover;
    bool m_clickCheck;
};

#endif // DISPLAYMODEITEM_H
