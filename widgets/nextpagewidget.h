#ifndef NEXTPAGEWIDGET_H
#define NEXTPAGEWIDGET_H

#include "settingsitem.h"
#include "labels/normallabel.h"
#include "nextbutton.h"

#include <QLabel>

namespace dcc {

class NextPageWidget : public SettingsItem
{
    Q_OBJECT

public:
    explicit NextPageWidget(QFrame *parent = 0);

    inline QString title() const { return m_title->text(); }
    void setTitle(const QString &title);
    void setValue(const QString &value);
//    void setDisplay(bool display);
//    bool display() const;

signals:
    void clicked() const;

private:
    NormalLabel *m_title;
    NormalLabel *m_value;
    dcc::widgets::NextButton *m_nextPageBtn;
};

}
#endif // NEXTPAGEWIDGET_H