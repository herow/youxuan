#include "comboboxdelegate.h"
#include <QComboBox>

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
       if(index.column() ==2||index.column() == 3||index.column() == 7) // 假如模型的第0列为公司名
       {
           QComboBox *comboEditor = qobject_cast<QComboBox *>(editor);
           if (comboEditor)
           {
               int i = comboEditor->findText(index.model()->data(index, Qt::EditRole).toString()); // 在comboBox组件中查找model中的当前公司名
               comboEditor->setCurrentIndex(i); // 设成model中的当前公司名
           }
       }
       else
       {
           return QStyledItemDelegate::setEditorData(editor, index);
       }
}
void ComboBoxDelegate::setModelData(QWidget *editor,
                  QAbstractItemModel *model,
                  const QModelIndex &index) const
{
       if(index.column() ==2||index.column() == 3||index.column() == 7)
       {
           QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
           if(comboBox)
           {
               model->setData(index, comboBox->currentText());
           }
       }
       else
       {
           return QStyledItemDelegate::setModelData(editor, model, index);
       }
}
