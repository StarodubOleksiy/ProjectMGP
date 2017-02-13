#include "fmidelegate.h"

FmiDelegate::FmiDelegate()
{
}



QWidget *FmiDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

        QLineEdit *editor = new QLineEdit(parent);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        editor->setReadOnly(true);
         return editor;


}

void FmiDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
       QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
        if (textEditor) {
            textEditor->isUndoAvailable();
            textEditor->setReadOnly(true);
            //textEditor->setText(index.model()->data(index, Qt::EditRole).toString());

    }
}

void FmiDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

        QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
        if (textEditor) {
        textEditor->setReadOnly(true);


    }
}
