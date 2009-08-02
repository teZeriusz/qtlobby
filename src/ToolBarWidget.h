#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QtGui/QWidget>
#include "ui_ToolBarWidget.h"

class ToolBarWidget : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(ToolBarWidget)
public:
    explicit ToolBarWidget(QWidget *parent = 0);
    virtual ~ToolBarWidget();

    Ui::ToolBarWidget *ui;

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // TOOLBARWIDGET_H
