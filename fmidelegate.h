#ifndef FMIDELEGATE_H
#define FMIDELEGATE_H

#include <QItemDelegate>
#include <QLineEdit>

class FmiDelegate : public QItemDelegate
{
public:
    FmiDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

};

#endif // FMIDELEGATE_H
