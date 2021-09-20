#ifndef NOTEDITABLEITEMDELEGATE_H
#define NOTEDITABLEITEMDELEGATE_H

#include <QItemDelegate>

class NotEditableItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableItemDelegate(QObject *parent = 0): QItemDelegate(parent){


    }

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        return false;
    }
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    {
        return Q_NULLPTR;
    }


};
#endif // NOTEDITABLEITEMDELEGATE_H
