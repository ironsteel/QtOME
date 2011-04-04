#ifndef WORKSPACEWIDGET_HPP
#define WORKSPACEWIDGET_HPP

#include <QTreeWidget>
#include <QMouseEvent>

class WorkspaceWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit WorkspaceWidget(QWidget *parent = 0);
    void     mousePressEvent ( QMouseEvent * event );

signals:

public slots:

};

#endif // WORKSPACEWIDGET_HPP
